#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

//gera um numero aleatorio distribuido uniformemente entre 0 e 1
double uniforme()
{
  double u = rand() / ((double)RAND_MAX + 1);
  // u == 0 --> ln(u) <-- problema
  // limitando u entre (0,1]
  u = 1.0 - u;
  return u;
}

//gera o tempo por meio de uma distribuicao exponencial
double gera_tempo(double l)
{
  return (-1.0 / l) * log(uniforme());
}

double min(double n1, double n2)
{
  if (n1 < n2)
    return n1;
  return n2;
}
