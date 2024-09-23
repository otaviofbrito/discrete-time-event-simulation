#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

#include "metrics.h"
#include "little.h"

#define CSV_PATH "c_project/data/output.csv"

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    printf("Usage: %s seed parametro_chega parametro_saida tempo_simulacao\n", argv[0]);
    return EXIT_FAILURE;
  }

  unsigned int seed = atoi(argv[1]);
  double parametro_chegada = atof(argv[2]);
  double parametro_saida = atof(argv[3]);
  double tempo_simulacao = atof(argv[4]);

  const double param1 = parametro_chegada;
  const double param2 = parametro_saida;

  srand(seed);

  parametro_chegada = 1.0 / parametro_chegada;
  parametro_saida = 1.0 / parametro_saida;

  double tempo_decorrido = 0.0;

  double tempo_chegada = gera_tempo(parametro_chegada);
  double tempo_saida = DBL_MAX;

  unsigned long int fila = 0;
  unsigned long int fila_max = 0;

  double soma_ocupacao = 0.0;

  // iniciar variaveis de little
  little en = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};
  little ew_chegadas = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};
  little ew_saidas = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};

  // metricas
  double en_final = 0.0;
  double ew_final = 0.0;
  double lambda = 0.0;
  double little_error = 0.0;
  double ocupacao = 0.0;

  // Tempo inicial de calculo
  double tempo_calc = 100.0;

  // Criar arquivo csv
  FILE *file = fopen(CSV_PATH, "a");
  if (file == NULL)
  {
    printf("Error opening file!\n");
    return EXIT_FAILURE;
  }
  fprintf(file, "Time,Fila Max,Ocupacao,E[N],E[W],Lambda,Erro de Little,Chegada,Saida\n");

  while (tempo_decorrido <= tempo_simulacao)
  {
    tempo_decorrido = min(min(tempo_chegada, tempo_saida), tempo_calc);

    if (tempo_decorrido == tempo_chegada)
    {
      if (!fila)
      {
        tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
        soma_ocupacao += tempo_saida - tempo_decorrido;
      }
      fila++;
      fila_max = fila > fila_max ? fila : fila_max;

      tempo_chegada = tempo_decorrido + gera_tempo(parametro_chegada);

      // little
      littles_calc(&en, tempo_decorrido);
      littles_calc(&ew_chegadas, tempo_decorrido);
      en.num_eventos++;
      ew_chegadas.num_eventos++;
    }
    else if (tempo_decorrido == tempo_saida)
    {
      fila--;
      tempo_saida = DBL_MAX;
      if (fila)
      {
        tempo_saida = tempo_decorrido + gera_tempo(parametro_saida);
        soma_ocupacao += tempo_saida - tempo_decorrido;
      }

      // little
      littles_calc(&en, tempo_decorrido);
      littles_calc(&ew_saidas, tempo_decorrido);
      en.num_eventos--;
      ew_saidas.num_eventos++;
    }
    // Calcula métricas
    else
    {
      //atualiza os 3 gráficos
      littles_calc(&en, tempo_decorrido);
      littles_calc(&ew_chegadas, tempo_decorrido);
      littles_calc(&ew_saidas, tempo_decorrido);

      en_final = en.soma_areas / tempo_decorrido;
      ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
      lambda = ew_chegadas.num_eventos / tempo_decorrido;
      ocupacao = soma_ocupacao / tempo_decorrido;
      little_error = en_final - (lambda * ew_final);

      // Escrever no arquivo CSV
      fprintf(file, "%f,%lu,%f,%f,%f,%f,%f,%f,%f\n",
              tempo_decorrido, fila_max, ocupacao, en_final, ew_final, lambda, little_error, param1, param2);

      // Atualizar o próximo tempo para calcular métricas
      tempo_calc += 100.0;
    }
  }
  fclose(file);
  littles_calc(&ew_chegadas, tempo_decorrido);
  littles_calc(&ew_saidas, tempo_decorrido);

  en_final = en.soma_areas / tempo_decorrido;
  ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
  lambda = ew_chegadas.num_eventos / tempo_decorrido;
  ocupacao = soma_ocupacao / tempo_decorrido;
  little_error = en_final - (lambda * ew_final);

  printf("\nMaior tamanho de fila alcancado: %ld\n", fila_max);
  printf("Ocupacao: %lf\n", ocupacao);
  printf("E[N]: %lf\n", en_final);
  printf("E[W]: %lf\n", ew_final);
  printf("Erro de Little: %lf\n", little_error);

  // Adicionar ocupacao e data ao nome do arquivo csv para identificação
  int file_ocup = (int)(round(ocupacao * 100));
  char new_name[50];

  // Obter o tempo atual
  time_t now = time(NULL);
  struct tm *tm_info = localtime(&now);

  // Formatar a data e hora
  char time_str[20];
  strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", tm_info);

  sprintf(new_name, "c_project/data/output_%s_%d.csv", time_str ,file_ocup);

  if (rename(CSV_PATH, new_name) != 0)
  {
    perror("Error renaming file");
  }

  return EXIT_SUCCESS;
}
