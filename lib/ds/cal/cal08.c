/*
 *  FILE ~/usr/planner/cal08.c
 *
 *  written:       1995-06-10
 *  latest update: 1995-06-10
 *
 */

#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int cal_reset_alternative_view (struct YEAR_INFO *yi)
{
  int z;
  int s;

  if (yi == (struct YEAR_INFO *) 0) return -1;

  for (z= 0; z < YI_AV_LINES; z++)
    for (s= 0; s < YI_AV_COLUMNS; s++)
      yi->YI_av [z][s]= (struct DAY_INFO *) 0;

  return 0;
}
