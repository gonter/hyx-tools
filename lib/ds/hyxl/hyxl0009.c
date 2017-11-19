/*
 *  FILE %ds/hyxl/hyxl0009.c
 *
 *  written:       1996-03-24
 *  latest update: 1996-10-13 16:43:20
 *  $Id: hyxl0009.c,v 1.4 2005/09/04 20:27:37 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gg/dates.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

#define ONE_DAY 86400L

/* ------------------------------------------------------------------------ */
char *hyx_translate_special_frame (const char *s)
{
#define _today          1
#define _tomorrow       2
#define _yesterday      3
#define _this_month     4
#define _next_month     5
#define _last_month     6
  int mode= 0;
  long xtime;
  long time_offset= 0L;
  char *cp= (char *) 0;
#define fmt_date        1
  int fmt= 0;
  int date_fmt;

  if (strcmp (s, "$$today") == 0)       mode= _today;                   else
  if (strcmp (s, "$$tomorrow") == 0)    mode= _tomorrow;                else
  if (strcmp (s, "$$yesterday") == 0)   mode= _yesterday;               else
  if (strcmp (s, "$$this_month") == 0)  mode= _this_month;              else
  if (strcmp (s, "$$next_month") == 0)  mode= _next_month;              else
  if (strcmp (s, "$$last_month") == 0)  mode= _last_month;

  switch (mode)
  {
    case _today:
      date_fmt=         DATIMfmt_date;
      time_offset=      0L;
      fmt=              fmt_date;
      break;

    case _tomorrow:
      date_fmt=         DATIMfmt_date;
      time_offset=      ONE_DAY;
      fmt=              fmt_date;
      break;

    case _yesterday:
      date_fmt=         DATIMfmt_date;
      time_offset=      -ONE_DAY;
      fmt=              fmt_date;
      break;

    case _this_month:
      date_fmt=         DATIMfmt_this_month;
      time_offset=      0L;
      fmt=              fmt_date;
      break;

    case _next_month:
      date_fmt=         DATIMfmt_next_month;
      time_offset=      0L;
      fmt=              fmt_date;
      break;

    case _last_month:
      date_fmt=         DATIMfmt_last_month;
      time_offset=      0L;
      fmt=              fmt_date;
      break;
  }

  switch (fmt)
  {
    case fmt_date:
      xtime= time ((time_t *) 0);
      xtime += time_offset;

      if ((cp= malloc (12)) != (char *) 0)
        _actual_datim (cp, date_fmt, xtime);
  }

  return cp;
}
