/*
 *  FILE %ds/cal/dt003b.c
 *
 *  print current date in a readable format in
 *  one large word
 *
 *  written:       2000-01-16
 *  latest update: 2000-01-16 20:19:00
 *
 */

#include <stdio.h>
#include <time.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int print_date_time_token (FILE *fo)
{
  time_t tt;
  struct tm *tm_s;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  fprintf (fo, "%04d-%02d-%02d_%02d:%02d:%02d",
           1900+tm_s->tm_year, tm_s->tm_mon+1, tm_s->tm_mday,
           tm_s->tm_hour, tm_s->tm_min,   tm_s->tm_sec);

  return 0;
}

#ifdef MAIN
int main (int argc, char *argv [])
{
  print_date_time_token (stdout);
  fputc ('\n', stdout);
}
#endif

