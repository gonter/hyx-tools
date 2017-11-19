/*
 *  FILE %ds/cal/cal04exp.c
 *
 *  written:       1998-08-22
 *  latest update: 1998-08-22 20:51:38
 *
 */

#include <stdio.h>
#include <gg/dates.h>

/* ------------------------------------------------------------------------ */
static char *TY []= { "?", "F", "V" };
static char *CL []= { "S", "N", "H" };

/* ------------------------------------------------------------------------ */
int export_holidays (
FILE *fo,
struct DAY_INFO_EXTRA de [])
{
  struct DAY_INFO_EXTRA *dep;
  int de_num;

  for (de_num= 0;; de_num++)
  {
    dep= &de [de_num];

    if (dep->DAYIE_country == (char *) 0) break;
    fprintf (fo, "%s:%s:%s:%s:%d:%d:%d:%d\n",
             dep->DAYIE_country,
             dep->DAYIE_description,
             TY [dep->DAYIE_type],
             CL [dep->DAYIE_class],
             dep->DAYIE_month,
             dep->DAYIE_day,
             dep->DAYIE_year_first,
             dep->DAYIE_year_last);
  }

  return de_num;
}

int main (int argc, char *argv [])
{
  FILE *fo;
#ifdef MSDOS
  argc; argv;
#endif

  fo= fopen ("@cal.exp", "wb");
  export_holidays (fo, AT_holiday);
  fclose (fo);

  return 0;
}
