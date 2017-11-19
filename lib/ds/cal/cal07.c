/*
 *  FILE %ds/cal/cal07.c
 *
 *  written:       1994-12-05
 *  latest update: 1998-08-04 12:49:53
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int print_calendar (
FILE *fo,
int year_from,
int year_to,
int print_what,
char *pfx)
{
  int year;
  int year_prev;
  int year_next;
  struct YEAR_INFO *year_info;

  if (print_what & CAL_PRINT_root_frame)
  {
    fprintf (fo, "<Frame $$root>\n");
    for (year= year_from; year <= year_to; year++)
    {
      /* print_yi_year (fo, year_info, year, "", 0, 0); */
      fprintf (fo, "<hyx.l fr=\"%d%s\" tdc=hyx.l tdp=4>%d",
               year, pfx, year);
      if (print_what & CAL_PRINT_alternative_view)
        fprintf (fo, "  <hyx.l fr=\"%d%s overview\" tdc=hyx.l tdp=8>overview",
                 year, pfx);
      fputc ('\n', fo);
    }

    fprintf (fo, "<hyx.l fr=\"$$index\" tdc=hyx.l tdp=7>$$index");
    /* fprintf (fo, "  <hyx.l fr=\"$$md5\" tdc=hyx.l tdp=5>$$md5"); */
    fprintf (fo, "\n</Frame>\n");
  }

  for (year= year_from; year <= year_to; year++)
  {
    year_prev= (year > year_from) ? year-1 : 0;
    year_next= (year < year_to)   ? year+1 : 0;

    if ((year_info= calloc (sizeof (struct YEAR_INFO), 1))
         == (struct YEAR_INFO *) 0)
    {
      fprintf (stderr, "can't allocated YEAR_INFO data structure!\n");
      break;
    }

    setup_year_info (year_info, year);
    fixup_extra_information (year_info, AT_holiday);

    if (print_what & CAL_PRINT_year)
      print_yi_year (fo, year_info, year, (char *) 0, year_prev, year_next,
                     pfx);
    if (print_what & CAL_PRINT_months)
      print_yi_months (fo, year_info, year_prev, year_next, pfx);
    if (print_what & CAL_PRINT_days)
      print_yi_days (fo, year_info, pfx);

    if (print_what & CAL_PRINT_alternative_view)
    {
      cal_reset_alternative_view (year_info);
      cal_setup_alternative_view (year_info);
      cal_print_alternative_view (fo, year_info, pfx);
    }

    cal_reset_year_info (year_info);
    free (year_info);
  }

  return 0;
}
