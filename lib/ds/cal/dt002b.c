/*
 *  FILE %ds/cal/dt002b.c
 *
 *  Ermittlung des aktuelle Jahres
 *
 *  written:       1994-12-05
 *  latest update: 1998-08-04 12:31:22
 *
 */

#include <time.h>
#include <stdio.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int get_current_year ()
{
  struct tm *tm_s;
  time_t tt;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  return 1900+tm_s->tm_year;
}
