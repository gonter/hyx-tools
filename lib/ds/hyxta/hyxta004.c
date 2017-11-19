/*
 *  FILE ~/usr/ds/hyxta/hyxta004.c
 *
 *  textual analysis:
 *  category flags
 *
 *  written:       1990 11 11
 *  latest update: 1995-03-30: moved to %ds/hyxta
 *
 */

#include <gg/parse.h>
#include <gg/ta.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
static long CAT_BITS [TA_CAT_CODES] =
{
  TA_CATF_other,
  TA_CATF_control1,
  TA_CATF_control2,
  TA_CATF_small,
  TA_CATF_capital,
  TA_CATF_digit,
  TA_CATF_nat_small,
  TA_CATF_nat_capital,
  TA_CATF_nat_currency,
  TA_CATF_greek,
  TA_CATF_graphic,
  TA_CATF_math1,
  TA_CATF_math2,
  TA_CATF_sond1,
  TA_CATF_sond2,
  TA_CATF_sond3,
  TA_CATF_nat_satz,
  TA_CATF_satz1,
  TA_CATF_satz2,
  TA_CATF_satz3,
  TA_CATF_satz4,
  TA_CATF_space1,
  TA_CATF_space2,
  TA_CATF_space3,
  TA_CATF_ligature
} ;

/* ------------------------------------------------------------------------ */
long hyx_ta_get_cat_flags (int cat)
{
  if (cat < 0) return 0L;
  if (cat >= TA_CAT_CODES) return TA_CATF_other;

  return CAT_BITS [cat];
}

/* ------------------------------------------------------------------------ */
int hyx_ta_set_cat_flags (int cat, long catf)
{
  if (cat < 0 || cat >= TA_CAT_CODES) return -1;
  CAT_BITS [cat]= catf;

  return 0;
}
