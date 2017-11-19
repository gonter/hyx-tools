/*
 *  FILE %ned/08/ned0865.c
 *
 *  written:       1991 07 05
 *                 1994-04-10: renamed from p_set_HLINK to p_set_hyx_l
 *  latest update: 1998-08-15 12:43:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_set_hyx_l ()
{
  ned_wc_feature_create (aw, Ftype_hyx_l, FTR_EDIT_ALL_COND, (char *) 0);
  /* dont open the feature window if the link came from memory */
}
