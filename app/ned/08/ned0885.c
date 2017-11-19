/*
 *  FILE %ned/08/ned0885.c
 *
 *  written:       1994-04-10
 *  latest update: 1998-08-15 12:36:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_set_lookup_tag ()
{
  ned_wc_feature_create (aw, Ftype_lookup, FTR_EDIT_NONE, (char *) 0);
  /* p_link_feature (); */
}
