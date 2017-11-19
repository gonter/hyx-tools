/*
 *  FILE %ds/cal/dt035.c
 *
 *  return julian day of a given day in a month
 *
 *  written:       1995-06-25
 *  latest update: 1997-01-15 21:54:24
 *
 */

#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int get_day_index (struct YEAR_INFO *yi, int mon, int day)
{
  int de_mon;
  int idx;

  de_mon= mon - 1;
  if (de_mon < 0 || de_mon > 11) return -1;

  idx= yi->YI_month_beg [de_mon];
  idx += day - 1;

  return idx;
}
