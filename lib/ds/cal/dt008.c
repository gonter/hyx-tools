/*
 *  FILE ~/usr/sbr/dt008.c
 *
 *  modify a given date by a number of days
 *
 *  written:       1992 08 30
 *  latest update: 1994-10-16
 *
 */

#include <sys/types.h>
#include <time.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int modify_date (struct tm *d, int delta)
{
  int dom;

  if (delta == 0) return 0;

  if (delta < 0)
  {
    delta= -delta;
    d->tm_wday= (d->tm_wday-(delta%7)+7)%7;
    while (delta > d->tm_mday)
    {
      delta -= d->tm_mday;
      if (d->tm_mon == 0)
      {
        d->tm_year--;
        d->tm_mon= 11;
      }
      else d->tm_mon--;
      d->tm_mday= days_of_month (d->tm_year, d->tm_mon+1);
    }
    d->tm_mday -= delta;
  }
  else
  {
    d->tm_wday= (d->tm_wday+(delta%7))%7;
    for (;;)
    {
      dom= days_of_month (d->tm_year, d->tm_mon+1);
      if (delta + d->tm_mday <= dom) break;
      delta -= dom - d->tm_mday + 1;
      if (d->tm_mon == 11)
      {
        d->tm_year++;
        d->tm_mon= 0;
      }
      else d->tm_mon++;
      d->tm_mday= 1;
    }
    d->tm_mday += delta;
  }
  return 0;
}
