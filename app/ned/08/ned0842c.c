/*
 *  FILE %ned/08/ned0842c.c
 *
 *  search for a feature record at the current cursor position
 *
 *  returns the address of the pointer (!) where the found
 *  feature record is linked
 *
 *  written:       1996-07-26
 *  latest update: 1996-07-26  2:34:51
 *
 */

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FEATURE **ned_feature_find2 (struct WINDOWCTRL *wc, int range)
{
  if (wc == (struct WINDOWCTRL *) 0) return (struct FEATURE **) 0;

  return ned_feature_find (wc->WC_act, wc->cx + wc->hv - wc->ax, range);
}
