/*
 *  FILE %ds/cal/dt042.c
 *
 *  written:       1995-06-10
 *  latest update: 1995-12-03
 *
 */

#include <stdlib.h>
#include <memory.h>
#include <gg/strings.h>
#include <gg/dates.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int cal_reset_year_info (struct YEAR_INFO *yi)
{
  int i;
  struct DAY_INFO_EXTRA *de1, *de2;

  for (i= 0; i < YI_DI_cnt; i++)
  {
    for (de1= yi->YI_day_info [i].DAYI_extra;
         de1 != (struct DAY_INFO_EXTRA *) 0;
         de1= de2)
    {
      de2= de1->DAYIE_next;
      if (de1->DAYIE_type == DAYIET_variable)
      {
        free_or_what (de1->DAYIE_country);
        free_or_what (de1->DAYIE_description);
        free (de1);
      }
    }

    memset (&yi->YI_day_info [i], 0, sizeof (struct DAY_INFO));
  }

  return 0;
}
