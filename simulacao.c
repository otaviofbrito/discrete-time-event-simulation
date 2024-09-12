#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct
{
  unsigned long int num_eventos;
  double tempo_anterior;
  double soma_areas;
} little;

double uniforme()
{
  double u = rand() / ((double)RAND_MAX + 1);
  // u == 0 --> ln(u) <-- problema
  // limitando u entre (0,1]
  u = 1.0 - u;
  return u;
}

double gera_tempo(double l)
{
  return (-1.0 / l) * log(uniforme());
}

double min(double n1, double n2, double n3)
{
  if (n1 < n2 && n1 < n3)
    return n1;
  else if (n2 < n3)
    return n2;
  else
    return n3;
}

void inicia_little(little *n)
{
  n->num_eventos = 0;
  n->soma_areas = 0.0;
  n->tempo_anterior = 0.0;
}

int main()
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

  /**
   * variaveis little
   */

  little en;
  little ew_chegadas;
  little ew_saidas;
  inicia_little(&en);
  inicia_little(&ew_chegadas);
  inicia_little(&ew_saidas);

  double en_final = 0.0;
  double ew_final = 0.0;
  double lambda = 0.0;

  double tempo_calc = 100.0;

  FILE *file = fopen("output.csv", "a");
  if (file == NULL)
  {
    printf("Error opening file!\n");
    return 0;
  }

  // Write the CSV header
  fprintf(file, "Time,Fila Max,Ocupacao,E[N],E[W],Lambda,Erro de Little\n");

  while (tempo_decorrido <= tempo_simulacao)
  {
    tempo_decorrido = min(tempo_chegada, tempo_saida, tempo_calc);

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

      /**
       * little
       */
      en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
      en.num_eventos++;
      en.tempo_anterior = tempo_decorrido;

      ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
      ew_chegadas.num_eventos++;
      ew_chegadas.tempo_anterior = tempo_decorrido;
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

      /**
       * little
       */
      en.soma_areas += (tempo_decorrido - en.tempo_anterior) * en.num_eventos;
      en.num_eventos--;
      en.tempo_anterior = tempo_decorrido;

      ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;
      ew_saidas.num_eventos++;
      ew_saidas.tempo_anterior = tempo_decorrido;
    }
    else if (tempo_decorrido == tempo_calc)
    {

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

  ew_chegadas.soma_areas += (tempo_decorrido - ew_chegadas.tempo_anterior) * ew_chegadas.num_eventos;
  ew_saidas.soma_areas += (tempo_decorrido - ew_saidas.tempo_anterior) * ew_saidas.num_eventos;

  printf("Maior tamanho de fila alcancado: %d\n", fila_max);
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
