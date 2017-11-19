/*
 *  FILE %ds/cal/cal10.c
 *
 *  written:       1995-06-10
 *  latest update: 1996-03-24 17:21:19
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int cal_print_alternative_view (FILE *fo, struct YEAR_INFO *yi, char *pfx)
{
  int m;
  int z;
  int s;
  int j;
  struct DAY_INFO *di;
  struct DAY_INFO_EXTRA *de;

  if (fo == (FILE *) 0 || yi == (struct YEAR_INFO *) 0) return -1;

  fprintf (fo, "<Frame %d%s overview>",           yi->YI_year, pfx);
  fprintf (fo, "<hyx.l dir=view fr=\"%d%S\">",    yi->YI_year, pfx);
  fprintf (fo, "<hyx.l dir=up fr=$$root>\n");
  fprintf (fo, "%d overview\n\n",                 yi->YI_year);

  for (z= 0; z < YI_AV_LINES; z++)
  {
    if ((z%6) == 0)
    {
      for (j= 0; j < 3; j++)
      {
        m= (z/6)*3+j+1;
        fprintf (fo, "<hyx.l fr=\"%d-%02d%s\" tdp=3 tdc=hyx.l>%s",
                 yi->YI_year, m, pfx, MONTH_NAME [m]);
        for (s= 1; s <= 7; s++)
          fprintf (fo, " %s", DAY_OF_WEEK2 [s%7]);
        if (j < 2) fprintf (fo, " |");
      }
      fputc ('\n', fo);
    }

    for (s= 0; s < YI_AV_COLUMNS; s++)
    {
      if (s == 0) fprintf (fo, "   ");
      if (s == 7 || s == 14) fprintf (fo, " |   ");

      di= yi->YI_av [z][s];
      if (di == (struct DAY_INFO *) 0)
      {
        printf ("   ");
        continue;
      }

      printf (" <hyx.l fr=\"%d-%02d-%02d%s\" tdp=2 tdc=%s>%2d",
              di->DAYI_year, di->DAYI_month, di->DAYI_day, pfx,
              ((de= di->DAYI_extra) != (struct DAY_INFO_EXTRA *) 0
               && strcmp (de->DAYIE_country, "AT") == 0
               && de->DAYIE_class == DAYIEC_holiday
              ) ? "mark" : "hyx.l",
              di->DAYI_day);
    }

    fputc ('\n', fo);

    if ((z%6) == 5) fputc ('\n', fo);
  }
  fprintf (fo, "</Frame>\n");

  return 0;
}
