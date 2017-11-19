/*
 *  FILE %ned/01/ned0117.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 01 27: Revision
 *  latest update: 1997-01-19  0:27:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_nl2 ()        /* Ctrl N */
{
  int aif;

  if (aw->WC_edit_mode & EDIT_READ_ONLY) return;

  aif= aw->ai;
  aw->ai= 0;
  ned_wc_ins_nl (aw);
  aw->ai= aif;
  chk_updown (aw);
}
