/*
 *  FILE %usr/ds/cal/cal05.c
 *
 *  written:       1994-10-20
 *  latest update: 1998-08-04 13:19:58
 *
 */

#include <stdio.h>
#include <gg/dates.h>

static char *AT= "AT";
static char *US= "US";
static char *EU= "EU";

/* ------------------------------------------------------------------------ */
int fixup_extra_information (
struct YEAR_INFO *yi,
struct DAY_INFO_EXTRA de [])
{
  struct DAY_INFO *di;
  struct DAY_INFO_EXTRA *dep;
  int de_num;
  int idx;
  int current_year;
  int mon_easter;
  int day_easter;

  if (yi == (struct YEAR_INFO *) 0) return -1;

  current_year= yi->YI_year;

  /* unbewegliche Feiertage */
  for (de_num= 0;; de_num++)
  {
    dep= &de [de_num];

    if (dep->DAYIE_country == (char *) 0) break;
    dep->DAYIE_next= (struct DAY_INFO_EXTRA *) 0;

    if (current_year < dep->DAYIE_year_first
        || current_year > dep->DAYIE_year_last
       ) continue;

    switch (dep->DAYIE_type)
    {
      case DAYIET_fixed:
        idx= get_day_index (yi, dep->DAYIE_month, dep->DAYIE_day);
        fixup_day (yi, idx, dep);
        break;
    }
  }

  /* bewegliche Feiertage um Ostern */
  get_easter (current_year, &mon_easter, &day_easter);
  idx= get_day_index (yi, mon_easter, day_easter);

  /* NOTE: (1996-02-11 11:23:06) Aschermittwoch korrekt errechnet fuer 1995/96 */
  fixup_day (yi, idx-46, create_day_info_extra (AT, DAYIEC_note, "Aschermittwoch"));
  fixup_day (yi, idx-46, create_day_info_extra ("FR", DAYIEC_note, "Les Cenderes"));
  fixup_day (yi, idx-46, create_day_info_extra ("IT", DAYIEC_note, "Le Ceneri"));
  fixup_day (yi, idx-46, create_day_info_extra ("UK", DAYIEC_note, "Ash Wednesday"));

  fixup_day (yi, idx- 7, create_day_info_extra (AT, DAYIEC_holiday, "Palmsonntag"));
  fixup_day (yi, idx- 3, create_day_info_extra (AT, DAYIEC_holiday, "Gruendonnerstag"));
  fixup_day (yi, idx- 2, create_day_info_extra (AT, DAYIEC_holiday, "Karfreitag"));
  fixup_day (yi, idx,    create_day_info_extra (AT, DAYIEC_holiday, "Ostersonntag"));
  fixup_day (yi, idx+ 1, create_day_info_extra (AT, DAYIEC_holiday, "Ostermontag"));
  fixup_day (yi, idx+39, create_day_info_extra (AT, DAYIEC_holiday, "Christi Himmelfahrt"));
  fixup_day (yi, idx+49, create_day_info_extra (AT, DAYIEC_holiday, "Pfingstsonntag"));
  fixup_day (yi, idx+50, create_day_info_extra (AT, DAYIEC_holiday, "Pfingstmontag"));
  fixup_day (yi, idx+60, create_day_info_extra (AT, DAYIEC_holiday, "Fronleichnam"));

  /* bewegliche Feiertage um Weihnachten */
  /* Advent: 4 Sonntage vor dem 25. Dez. */
  idx= get_day_index (yi, 12, 25);
  for (di= &yi->YI_day_info [idx]; di->DAYI_wday != 0; di--) idx--;
  fixup_day (yi, idx-21, create_day_info_extra (AT, DAYIEC_note, "1. Advent"));
  fixup_day (yi, idx-14, create_day_info_extra (AT, DAYIEC_note, "2. Advent"));
  fixup_day (yi, idx- 7, create_day_info_extra (AT, DAYIEC_note, "3. Advent"));
  fixup_day (yi, idx,    create_day_info_extra (AT, DAYIEC_note, "4. Advent"));

  idx= get_day_index (yi, 12, 24);
  fixup_day (yi, idx,    create_day_info_extra (AT, DAYIEC_note, "Heiliger Abend"));

  /* Muttertag; 2. Sonntag im Mai */
#ifdef __OLD__ /* 1997-01-15 22:03:50 */
  idx= get_day_index (yi, 5, 1);
  for (di= &yi->YI_day_info [idx]; di->DAYI_wday != 0; di++) idx++;
  di++; idx++;
  for (                          ; di->DAYI_wday != 0; di++) idx++;
#endif /* __OLD__ 1997-01-15 22:03:50 */

  /* US holidays on mondays */
  idx= get_wday_index (yi, 5, DAYI_sunday, 2);
  fixup_day (yi, idx, create_day_info_extra (EU, DAYIEC_note, "Muttertag"));

  idx= get_wday_index (yi, 1, DAYI_monday, 3);
  fixup_day (yi, idx, create_day_info_extra (US, DAYIEC_holiday, "Martin Luther King's Birthday(sp?)"));

  idx= get_wday_index (yi, 2, DAYI_monday, 3);
  fixup_day (yi, idx, create_day_info_extra (US, DAYIEC_holiday, "Washington's Birthday(sp?)"));

  idx= get_wday_index (yi, 10, DAYI_monday, 2);
  fixup_day (yi, idx, create_day_info_extra (US, DAYIEC_holiday, "Columbus Day"));

  /* Sommerzeit */
  idx= get_wday_index (yi, 3, DAYI_sunday, 5);
  fixup_day (yi, idx, create_day_info_extra (EU, DAYIEC_note, "Sommerzeitanfang"));

  idx= -1;
  if (current_year >= 1996)
    idx= get_wday_index (yi, 10, DAYI_sunday, 5);
  if (current_year < 1996 && current_year > 1970) /* T2D: Sommerzeitende */
    idx= get_wday_index (yi, 9, DAYI_sunday, 5);

  if (idx != -1)
    fixup_day (yi, idx, create_day_info_extra (EU, DAYIEC_note, "Sommerzeitende"));

  return 0;
}
