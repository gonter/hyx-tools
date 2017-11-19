/*
 *  FILE ~/usr/sbr/dt002.c
 *
 *  Ermittlung der Datums und der Zeit
 *
 *  written:       1989 03 18: extrahiert aus e:\xerox\cr.c
 *  latest update: 1995-06-11
 *
 */

#include <time.h>
#include <stdio.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int actual_datim_int (
int *jahr,
int *monat,
int *tag,
int *stunde,
int *minute,
int *sekunde)
{
  struct tm *tm_s;
  time_t tt;

  tt= time ((time_t *) 0);
  tm_s= localtime (&tt);

  *jahr   = tm_s->tm_year;
  *monat  = tm_s->tm_mon+1;
  *tag    = tm_s->tm_mday;
  *stunde = tm_s->tm_hour;
  *minute = tm_s->tm_min;
  *sekunde= tm_s->tm_sec;

  return 0;
}
