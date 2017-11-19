/*
 *  FILE %ds/cal/dt004.c
 *
 *  prepare a RFC 822 date string
 *
 *  written:       1992 04 07
 *  latest update: 1997-11-26 13:24:13
 *
 */

#include <stdio.h>
#include <time.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static char *MONTHS [] =
{
  "Jan", "Feb", "Mar",
  "Apr", "May", "Jun",
  "Jul", "Aug", "Sep",
  "Oct", "Nov", "Dec"
};

/* ------------------------------------------------------------------------ */
static char *WEEK_DAYS [] =
{
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Huh"
} ;

/* ------------------------------------------------------------------------ */
void prepare_date (char *datum, char *tz, int max_line)
{
  struct tm *tm_s;
  time_t tt;

  if (max_line < 60) return;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  sprintf (datum, "%s, %d %s %04d %2d:%02d:%02d %s",
           WEEK_DAYS [tm_s->tm_wday],
           tm_s->tm_mday, MONTHS [tm_s->tm_mon], 1900+tm_s->tm_year,
           tm_s->tm_hour, tm_s->tm_min, tm_s->tm_sec,
           tz);
}
