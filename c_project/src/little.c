#include "little.h"

void littles_calc(little *e, double current_time)
{
  e->soma_areas += (current_time - e->tempo_anterior) * e->num_eventos;
  e->tempo_anterior = current_time;
}