/*
 *  FILE %ned/01/ned0120.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1996-05-23 16:16:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_jmp_boln ()        /* Spalte 0 */
{
  ned_w_jmp_in_line (aw, NEDJMP_BOLN, 0);
}
