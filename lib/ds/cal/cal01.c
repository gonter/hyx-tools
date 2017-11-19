/*
 *  FILE %ds/cal/cal01.c
 *
 *  CAL generator
 *
 *  written:       1994-10-17
 *  latest update: 1997-01-15 23:05:00
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int print_yi_year (
FILE *fo,
struct YEAR_INFO *yi,
int year,
char *frame_name,
int year_prev,
int year_next,
char *pfx)
{
  int num;              /* number of days in particular month               */
  int wnum= 1;          /* week number                                      */
  int dnum= 0;          /* day of year; 0..364 (365)                        */
  int mon;              /* current month                                    */

  num= (yi->YI_is_leap_year) ? 366 : 365;

  if (frame_name == (char *) 0)
  {
    fprintf (fo, "<Frame %d%s>", year, pfx);
    fprintf (fo, "<hyx.l dir=view fr=\"%d%s overview\">", year, pfx);
    if (year_prev != 0)
      fprintf (fo, "<hyx.l dir=prev fr=\"%d%s\">", year_prev, pfx);
    if (year_next != 0)
      fprintf (fo, "<hyx.l dir=next fr=\"%d%s\">", year_next, pfx);
  }
  else
  {
    if (frame_name [0])
      fprintf (fo, "<Frame %s>", frame_name);
  }
  fprintf (fo, "<hyx.l dir=up fr=$$root>\n");

  fprintf (fo, "%d\n\n", year);
  for (mon= 0; mon < 12; mon++)
  {
    fprintf (fo, "<hyx.l fr=\"%d-%02d%s\" tdc=hyx.l tdp=6>%2d %s\n",
            year, mon+1, pfx, mon+1, MONTH_NAME[mon+1]);
  }

  fputc ('\n', fo);
  if (frame_name == (char *) 0 || frame_name [0])
    fprintf (fo, "</Frame>\n");

  return 0;
}
