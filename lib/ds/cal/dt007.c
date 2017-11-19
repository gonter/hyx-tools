/*
 *  FILE %ds/cal/dt007.c
 *
 *  find out if given year is a leap year
 *
 *  written:       1992 08 30
 *  latest update: 1998-08-04 12:34:09
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int is_leap_year (int year)
{
  if (year < 1582) return (year % 4) ? 0 : 1;

  if ((year%4) != 0) return 0;
  if ((year%100) != 0) return 1;
  if ((year%400) != 0) return 0;

  return 1;
}
