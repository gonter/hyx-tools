/*
 *  FILE %ds/cal/dt041.c
 *
 *  written:       1994-10-17
 *  latest update: 1997-01-16  9:45:31
 *
 */

#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int setup_year_info (struct YEAR_INFO *yi, int year)
{
  int i;
  int j;
  int dom;
  int beg= 0;
  int dnum= 0;
  int mon;
  int wday;
  struct DAY_INFO *di;

  if (yi == (struct YEAR_INFO *) 0) return -1;

  yi->YI_year= year;
  yi->YI_is_leap_year= is_leap_year (year);
  wday= weekday (year, 1, 1);

  for (i= 0; i < 12; i++)
  {
    mon= i+1;
    dom= days_of_month (year, mon);

    yi->YI_month_beg [i]= beg;
    yi->YI_days_of_month [i]= dom;
    beg += dom;

    for (j= 0; j < dom; j++)
    {
      di= &(yi->YI_day_info [dnum]);
      di->DAYI_year= year;
      di->DAYI_month= mon;
      di->DAYI_day= j+1;
      di->DAYI_wday= wday;
      di->DAYI_extra= (struct DAY_INFO_EXTRA *) 0;
      wday= (wday == 6) ? 0 : wday+1;
      dnum++;
    }
  }

  return 0;
}
