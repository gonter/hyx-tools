/*
 *  FILE %ned/08/ned0861.c
 *
 *  written:       1991 07 05
 *  latest update: 1998-08-15 12:42:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_set_SGML_tag ()
{
  ned_wc_feature_create (aw, Ftype_SGML_TAG, 0, (char *) 0);
}
