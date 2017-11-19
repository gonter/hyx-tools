/*
 *  FILE %ned/08/ned0806.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1997-02-08 20:43:55
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_feature_set ()
{
  ned_wc_feature_create (aw, 0, FTR_EDIT_NONE, (char *) 0);
}
