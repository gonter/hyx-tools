/*
 *  FILE %ds/cal/cal06.c
 *
 *  CAL generator
 *
 *  written:       1994-10-20
 *  latest update: 1996-03-24 17:17:30
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int get_day_string (char *day_frame, struct DAY_INFO *di)
{
  sprintf (day_frame,
           "%d-%02d-%02d",
           di->DAYI_year,
           di->DAYI_month,
           di->DAYI_day);

  return 0;
}
