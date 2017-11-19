/*
 *  FILE %ds/cal/cal09.c
 *
 *  written:       1995-06-10
 *  latest update: 1995-12-03
 *
 */

#include <gg/dates.h>

#include <stdio.h>

/* ------------------------------------------------------------------------ */
int cal_setup_alternative_view (struct YEAR_INFO *yi)
{
  int m;
  int day;
  int dm;
  int dnum;
  int z;
  int sp;
  int spo;
  struct DAY_INFO *di;

  if (yi == (struct YEAR_INFO *) 0) return -1;

  for (m= 0; m < 12; m++)
  {
    dnum= yi->YI_month_beg [m];
    dm= yi->YI_days_of_month [m];
    di= &(yi->YI_day_info [dnum]);
    z= (m/3)*6;
    sp= di->DAYI_wday-1;
    if (sp < 0) sp= 6;
    spo= (m%3)*7;
/***** 1995-12-03 22:25:44
printf ("m=%d dm=%d z=%d sp=%d spo=%d\n", m, dm, z, sp, spo);
*************************/

    for (day= 0; day < dm; day++)
    {
      di= &(yi->YI_day_info [dnum++]);
      yi->YI_av [z][sp+spo]= di;
      if (++sp >= 7)
      {
        z++;
        sp= 0;
      }
    }
  }

  return 0;
}
