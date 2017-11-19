/*
 *  FILE %ds/cal/cal02.c
 *
 *  CAL generator
 *
 *  written:       1994-10-17
 *  latest update: 1997-01-15 23:07:59
 *  $Id: cal02.c,v 1.5 2011/08/25 01:24:33 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
static char day_frame_name [128];

/* ------------------------------------------------------------------------ */
int print_yi_months (
FILE *fo,
struct YEAR_INFO *yi,
int year_prev,
int year_next,
char *pfx)
{
  struct DAY_INFO *di;  /* information about a day                          */
  struct DAY_INFO_EXTRA *de;
  int num;              /* number of days in particular month               */
  int wnum;             /* week number                                      */
  int wyear;            /* given week number's year                         */
  int dnum= 0;          /* day of year; 0..364 (365)                        */
  int wday;             /* day of week; 0..6                                */
  char *dow3;           /* name of day week                                 */
  int mon;              /* current month                                    */
  int day;              /* current day in month                             */

  if (yi == (struct YEAR_INFO *) 0) return -1;

  num= (yi->YI_is_leap_year) ? 366 : 365;

  di= &(yi->YI_day_info [0]);
  switch (di->DAYI_wday)
  {
    case 0: wnum= 52; wyear= yi->YI_year-1; break;
    case 1:
    case 2:
    case 3:
    case 4: wnum= 1; wyear= yi->YI_year; break;
    case 5:
    case 6: wnum= 52; wyear= yi->YI_year-1; break;
  }

  for (mon= 0; mon < 12; mon++)
  {
    dnum= yi->YI_month_beg [mon];
    num= yi->YI_days_of_month [mon];
    di= &(yi->YI_day_info [dnum]);

    fprintf (fo, "<Frame %d-%02d%s>", di->DAYI_year, di->DAYI_month, pfx);

    if (mon > 0)
    {
      fprintf (fo, "<hyx.l fr=\"%d-%02d%s\" dir=prev>",
        di->DAYI_year, di->DAYI_month-1, pfx);
    }
    else
    {
      if (year_prev != 0)
        fprintf (fo, "<hyx.l fr=\"%d-12%s\" dir=prev>", year_prev, pfx);
    }

    if (mon < 11)
    {
      fprintf (fo, "<hyx.l fr=\"%d-%02d%s\" dir=next>",
        di->DAYI_year, di->DAYI_month+1, pfx);
    }
    else
    {
      if (year_next != 0)
        fprintf (fo, "<hyx.l fr=\"%d-01%s\" dir=next>", year_next, pfx);
    }

    fprintf (fo, "<hyx.l fr=\"%d%s\" dir=up>\n", di->DAYI_year, pfx);

    fprintf (fo, "%d-%02d %s\n\n",
            di->DAYI_year, di->DAYI_month, MONTH_NAME [di->DAYI_month]);

    fprintf (fo,
      "------  <mark id=\"%d-W%02d\" tdc=mark tdp=7>week %2d  ------\n",
      wyear, wnum, wnum);

    for (day= 0; day < num; day++)
    {
      di= &(yi->YI_day_info [dnum++]);
      wday= di->DAYI_wday;
      dow3= (wday >= 0 && wday <= 6) ? DAY_OF_WEEK3 [wday] : "XXX";
      get_day_string (day_frame_name, di);

      /***************
      fprintf (fo, "<hyx.l fr=\"%s%s\" tdc=hyx.l tdp=6>%2d %s %66s[%3d]\n",
              day_frame_name, pfx, di->DAYI_day, dow3, " ", dnum);
      ***************/
      fprintf (fo,
              "<hyx.l fr=\"%s%s\" tdc=hyx.l tdp=6>%2d %s",
              day_frame_name, pfx, di->DAYI_day, dow3);
      if ((de= di->DAYI_extra) != (struct DAY_INFO_EXTRA *) 0)
        printf ("  (%s) %s", de->DAYIE_country, de->DAYIE_description);
      fputc ('\n', fo);

      if (wday == 0)
      {
        wnum++;
        if (wnum >= 53)
        { /* new year */
	  wnum= 1;
	  wyear++;
          fprintf (fo,
            "------  <mark id=\"%d-W%02d\" tdc=mark tdp=7>week %2d  ------\n",
            di->DAYI_year+1, 1, 1);
        }
        else
        {
          fprintf (fo,
            "------  <mark id=\"%d-W%02d\" tdc=mark tdp=7>week %2d  ------\n",
            di->DAYI_year, wnum, wnum);
        }
      }
    }
    fprintf (fo, "</Frame>");
  }
  return 0;
}
