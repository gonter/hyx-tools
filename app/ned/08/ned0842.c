/*
 *  FILE %ned/08/ned0842.c
 *
 *  search for a feature record at the current cursor position
 *
 *  returns the address of the pointer (!) where the found
 *  feature record is linked
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1996-07-25 21:45:36
 *
 */

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
struct FEATURE **ned_feature_find3 (int range)
{
  if (aw == (struct WINDOWCTRL *) 0) return (struct FEATURE **) 0;

  return ned_feature_find (aw->WC_act, aw->cx + aw->hv - aw->ax, range);
}
