/*
 *  FILE %ned/01/ned0129.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1997-08-03  9:46:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_split_join ()
{
  if (aw->WC_act == (struct LINE *) 0) return;

  if (aw->cx - aw->ax + aw->hv == aw->WC_act->lng)
    ned_del_char_right ();
  else p_nl2 ();
}
