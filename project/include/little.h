#pragma once

typedef struct
{
  unsigned long int num_eventos;
  double tempo_anterior;
  double soma_areas;
} little;

void littles_calc(little *e, double current_time);