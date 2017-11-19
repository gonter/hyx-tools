/*
 *  FILE %ds/cal/dt037.c
 *
 *  fixup one day entry
 *
 *  written:       1995-06-25
 *  latest update: 1998-08-04 13:24:38
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
struct DAY_INFO *fixup_day (
struct YEAR_INFO *yi,
int idx,
struct DAY_INFO_EXTRA *dep)
{
  struct DAY_INFO *di;
  struct DAY_INFO_EXTRA *dp, **ap;

  if (idx < 0
      || idx > 365
      || dep == (struct DAY_INFO_EXTRA *) 0
     )
    return (struct DAY_INFO *) 0;

  di= &yi->YI_day_info [idx];
  ap= &di->DAYI_extra;
  while ((dp= *ap) != (struct DAY_INFO_EXTRA *) 0)
  {
    ap= &dp->DAYIE_next;
  }

  *ap= dep;

  return di;
}
