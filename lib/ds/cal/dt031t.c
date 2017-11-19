/*
 *  FILE %ds/cal/dt031t.c
 *
 *  written: 1996-11-10
 *  latest update: 1996-11-10 15:15:19
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
char *examples [] =
{
  "1996-11-20",
  "Feb 12, 1996",
  "11/12/96",
  "22.3.97",
  "3.27.97",
  "25. August 1996, 18:00:20",
  "1996-11-10 15:49:50",
  (char *) 0
} ;

/* ------------------------------------------------------------------------ */
int main (void);
int main ()
{
  char *ex;
  int k;
  int jahr, mon, tag, std, minutes, sek, x_timezone;
  long v;
  int t, xsj, xt;

  for (k= 0; (ex= examples [k]) != (char *) 0; k++)
  {
    analyze_date (ex, &jahr, &mon, &tag, &std, &minutes, &sek, &x_timezone);
    printf ("string: '%s'\n", ex);
    printf ("  jahr=%d mon=%d tag=%d\n", jahr, mon, tag);
    printf ("  std=%d min=%d sek=%d tz=%d\n\n", std, minutes, sek,x_timezone);

    valid_datum (jahr, mon, tag, &v, &t, &xsj, &xt);
    printf ("  v=%ld t=%d xsj=%d xt=%d\n", v, t, xsj, xt);
  }

  return 0;
}
