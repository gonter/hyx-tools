/*
 *  FILE %ned/01/ned0121.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1997-02-09 17:21:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_jmp_eoln ()        /* letzte Spalte */
{
  ned_w_jmp_in_line (aw, NEDJMP_EOLN, 0);
}
