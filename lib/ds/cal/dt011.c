/*
 *  FILE %ds/cal/dt011.c
 *
 *  written:       1992 04 07
 *  latest update: 1997-01-16  9:44:06
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int weekday (int jahr, int mon, int tag)
{
  long v;

  v= day_number (jahr, mon, tag);
  if (v < 0L) return -1;
  return (int) ((v+6L)%7L);      /* 0..Sun, 6..Sat */
}
