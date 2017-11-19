/*
 *  FILE %ds/cal/dt010.c
 *
 *  written:       1992 04 07
 *  latest update: 1997-01-16  9:44:20
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long day_number (int jahr, int mon, int tag)
{
  long x1, x2, x3, x4, x4a, v;

  if (jahr <= 1582
      || mon < 1 || mon > 12
      || tag < 1 || tag > 31
     ) return -1L;

  x1 = 365L*((long) jahr) + (long) (31*(mon-1) + tag);

  if (mon <= 2)
  {
    x2  = 0L;
    x3  = (long) ((jahr-1)/4);
    x4a = (long) ((jahr-1)/100+1);
  }
  else
  {
    x2  = (long) ((mon*4 + 23)/10);
    x3  = (long) (jahr/4);
    x4a = (long) (jahr/100+1);
  }

  x4 = (x4a*3L)/4L;
  v  = x1 - x2;
  v += x3;
  v -= x4;

  return v;
}
