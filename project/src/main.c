#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

#include "metrics.h"
#include "little.h"

#define CSV_PATH "./data/output.csv"

int main(int argc, char *argv[])
{
  srand(100);
  double parametro_chegada;
  printf("Informe o tempo médio entre as chegadas (s): ");
  scanf("%lf", &parametro_chegada);
  parametro_chegada = 1.0 / parametro_chegada;

  double parametro_saida;
  printf("Informe o tempo médio de atendimento (s): ");
  scanf("%lf", &parametro_saida);
  parametro_saida = 1.0 / parametro_saida;

  double tempo_simulacao;
  printf("Informe o tempo de simulacao (s): ");
  scanf("%lf", &tempo_simulacao);

  double tempo_decorrido = 0.0;

  double tempo_chegada = gera_tempo(parametro_chegada);
  double tempo_saida = DBL_MAX;

  unsigned long int fila = 0;
  unsigned long int fila_max = 0;

  double soma_ocupacao = 0.0;

  // little's variables
  little en = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};
  little ew_chegadas = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};
  little ew_saidas = {.num_eventos = 0, .soma_areas = 0.0, .tempo_anterior = 0.0};

  double en_final = 0.0;
  double ew_final = 0.0;
  double lambda = 0.0;

  double tempo_calc = 100.0;

  FILE *file = fopen(CSV_PATH, "a");
  if (file == NULL)
  {
    printf("Error opening file!\n");
    return 0;
  }
  fprintf(file, "Time,Fila Max,Ocupacao,E[N],E[W],Lambda,Erro de Little\n");

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
    // Calculate pontual little's metrics
    else if (tempo_decorrido == tempo_calc)
    {

      littles_calc(&en, tempo_decorrido);
      littles_calc(&ew_chegadas, tempo_decorrido);
      littles_calc(&ew_saidas, tempo_decorrido);

      en_final = en.soma_areas / tempo_decorrido;
      ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
      lambda = ew_chegadas.num_eventos / tempo_decorrido;

      // Escrever no arquivo CSV
      fprintf(file, "%f,%lu,%f,%f,%f,%f,%f\n",
              tempo_decorrido, fila_max, soma_ocupacao / tempo_decorrido, en_final, ew_final, lambda, en_final - lambda * ew_final);

      // Atualizar o próximo tempo para calcular métricas
      tempo_calc += 100.0;
    }
  }

  printf("\nMaior tamanho de fila alcancado: %ld\n", fila_max);
  printf("Ocupacao: %lf\n", soma_ocupacao / tempo_decorrido);

  en_final = en.soma_areas / tempo_decorrido;
  ew_final = (ew_chegadas.soma_areas - ew_saidas.soma_areas) / ew_chegadas.num_eventos;
  lambda = ew_chegadas.num_eventos / tempo_decorrido;

  printf("E[N]: %lf\n", en_final);
  printf("E[W]: %lf\n", ew_final);
  printf("Erro de Little: %lf\n", en_final - lambda * ew_final);

  fclose(file);

  return 0;
}
