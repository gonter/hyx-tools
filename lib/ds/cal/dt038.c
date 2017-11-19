/*
 *  FILE %ds/cal/dt038.c
 *
 *  return day of the n-th given weekday in a month
 *
 *  written:       1997-01-15
 *  latest update: 1998-08-04 12:42:45
 *
 */

#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
int get_wday_index (struct YEAR_INFO *yi, int mon, int wday, int num)
{
  int idx;
  int days_of_month;
  int wday_idx= -1;
  struct DAY_INFO *di;

  if (yi == (struct YEAR_INFO *) 0
      || mon < 1
      || mon > 12
     )
    return -1;

  idx= get_day_index (yi, mon, 1);
  days_of_month= yi->YI_days_of_month [mon-1];
  di= &yi->YI_day_info [idx];;

    while (num-- > 0)
    {
      while (di->DAYI_wday != wday) { di++; idx++; days_of_month--; }

      if (days_of_month < 0) break;     /* 5.th means last weekday */

      wday_idx= idx;
      if (num == 0) break;

      di++;
      idx++;
      days_of_month--;
    }

  return wday_idx;
}
