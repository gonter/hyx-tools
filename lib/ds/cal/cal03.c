/*
 *  FILE %ds/cal/cal03.c
 *
 *  CAL generator
 *
 *  written:       1994-10-17
 *  latest update: 1997-02-25 19:47:47
 *  $Id: cal03.c,v 1.3 2011/08/25 01:24:33 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
static char day_frame_name   [64];
static char day_frame_before [64];
static char day_frame_next   [64];

/* ------------------------------------------------------------------------ */
int print_yi_days (FILE *fo, struct YEAR_INFO *yi, char *pfx)
{
  struct DAY_INFO *di;  /* information about a day                          */
  struct DAY_INFO_EXTRA *de;
  int num;              /* number of days in particular month               */
  int ynum;             /* number of days in this year                      */
  int wnum;             /* week number                                      */
  int dnum= 0;          /* day of year; 0..364 (365)                        */
  int mon;              /* current month                                    */
  int day;              /* current day in month                             */
  int wday;
  char *dow3;           /* day of week, three chars                         */

  if (yi == (struct YEAR_INFO *) 0) return -1;

  ynum= (yi->YI_is_leap_year) ? 366 : 365;

  di= &(yi->YI_day_info [0]);
  wnum= (di->DAYI_wday == 1) ? 1 : 0;

  for (mon= 0; mon < 12; mon++)
  {
    dnum= yi->YI_month_beg [mon];
    num= yi->YI_days_of_month [mon];
    di= &(yi->YI_day_info [dnum]);

    for (day= 0; day < num; day++)
    {
      day_frame_before [0]= 0;
      day_frame_next [0]= 0;
      if (dnum > 0)
      {
        di= &(yi->YI_day_info [dnum-1]);
        get_day_string (day_frame_before, di);
      }

      di= &(yi->YI_day_info [dnum]);
      get_day_string (day_frame_name, di);

      if (di->DAYI_month != 12 || di->DAYI_day != 31)
      {
        di= &(yi->YI_day_info [dnum+1]);
        get_day_string (day_frame_next, di);
      }

      di= &(yi->YI_day_info [dnum]);

      fprintf (fo, "<Frame %s%s>", day_frame_name, pfx);
      if (day_frame_before [0] != 0)
        fprintf (fo, "<hyx.l fr=\"%s%s\" dir=prev>", day_frame_before, pfx);
      if (day_frame_next [0] != 0)
        fprintf (fo, "<hyx.l fr=\"%s%s\" dir=next>", day_frame_next, pfx);
      fprintf (fo, "<hyx.l fr=\"%d-%02d%s\" dir=up>\n",
               di->DAYI_year, di->DAYI_month, pfx);

      wday= di->DAYI_wday;
      dow3= (wday >= 0 && wday <= 6) ? DAY_OF_WEEK3 [wday] : "XXX";

      fprintf (fo, "<date>%s</date> %-50s [W %2d/D %3d/DL %3d]\n",
               day_frame_name, dow3, wnum, dnum+1, ynum-dnum-1);
      for (de= di->DAYI_extra;
           de != (struct DAY_INFO_EXTRA *) 0;
           de= de->DAYIE_next)
        printf ("(%s) %s\n", de->DAYIE_country, de->DAYIE_description);
      fprintf (fo, "\n</Frame>\n");
      if (di->DAYI_wday == 0) ++wnum;
      dnum++;
    }

  }
  return 0;
}
