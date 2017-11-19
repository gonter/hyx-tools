/*
 *  FILE ~/usr/ds/cal/dt011t.c
 *
 *  written:       1992 04 07
 *  latest update: 1995-06-25
 *
 */

#include <stdio.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  int year, month, day;
  int m_easter, d_easter;
  long v;
  int d;
  char *dow3;

  argc; argv;

  for (;;)
  {
    printf ("enter date: (yyyy mm dd) ");
    scanf ("%d", &year);
    scanf ("%d", &month);
    scanf ("%d", &day);
    v= day_number (year, month, day);
    d= weekday (year, month, day);

    get_easter (year, &m_easter, &d_easter);

    dow3= (d >= 0 && d <= 6) ? DAY_OF_WEEK3 [d] : "Schlingel ;)";
    printf ("%d %02d %02d = %7ld = %d %s\n", year, month, day, v, d, dow3);
    printf ("Ostern: %d %d\n", m_easter, d_easter);
  }

  return 0;
}
