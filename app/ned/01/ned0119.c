/*
 *  FILE %ned/01/ned0119.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1996-05-23 16:10:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_ax_lng ()        /* CTRL-J: Spalte 0 oder letzte Spalte */
{
  ned_w_jmp_in_line (aw, NEDJMP_AXLNG, 0);
}
