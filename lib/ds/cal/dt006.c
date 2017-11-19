/*
 *  FILE %ds/cal/dt006.c
 *
 *  get then number of days in the given month
 *
 *  written:       1992 08 30
 *  latest update: 1997-01-16  9:47:44
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static int DAYS_OF_MONTH [] =
{
/* (invalid)    */  -1,
/* January      */  31,
/* Februar      */  28,
/* March        */  31,
/* April        */  30,
/* May          */  31,
/* June         */  30,
/* July         */  31,
/* August       */  31,
/* September    */  30,
/* October      */  31,
/* November     */  30,
/* December     */  31
} ;

/* ------------------------------------------------------------------------ */
int days_of_month (int year, int month)
{
  if (month <= 0 || month > 12) return -1;

  if (month == 2) return (is_leap_year (year)) ? 29 : 28;
  return DAYS_OF_MONTH [month];
}
