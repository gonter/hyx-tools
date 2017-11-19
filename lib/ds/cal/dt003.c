/*
 *  FILE ~/usr/sbr/dt003.c
 *
 *  print current date in a readable format
 *
 *  written:       1990 11 03
 *  latest update: 1995-08-03
 *
 */

#include <stdio.h>
#include <time.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int print_date_time (FILE *fo)
{
  time_t tt;
  struct tm *tm_s;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  fprintf (fo, "%04d-%02d-%02d %2d:%02d:%02d",
           1900+tm_s->tm_year, tm_s->tm_mon+1, tm_s->tm_mday,
           tm_s->tm_hour, tm_s->tm_min,   tm_s->tm_sec);

  return 0;
}
