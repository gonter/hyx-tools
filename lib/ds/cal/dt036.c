/*
 *  FILE %ds/cal/dt036.c
 *
 *  return month and day of easter
 *
 *  written:       1995-06-25
 *  latest update: 1996-02-04 11:28:30
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
struct DAY_INFO_EXTRA *create_day_info_extra (
char *country,
int d_class,
char *description)
{
  struct DAY_INFO_EXTRA *di;

  if ((di= (struct DAY_INFO_EXTRA *)
           calloc (sizeof (struct DAY_INFO_EXTRA), 1))
      == (struct DAY_INFO_EXTRA *) 0)
    return (struct DAY_INFO_EXTRA *) 0;

  di->DAYIE_country= strdup (country);
  di->DAYIE_description= strdup (description);
  di->DAYIE_type= DAYIET_variable;
  di->DAYIE_class= d_class;
  di->DAYIE_month= 0;
  di->DAYIE_day= 0;
  di->DAYIE_year_first= 0;
  di->DAYIE_year_last= 0;

  return di;
}
