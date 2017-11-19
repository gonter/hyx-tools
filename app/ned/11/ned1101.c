/*
 *  FILE %ned/11/ned1101.c
 *
 *  Such- und Ersetzungsfunktionen
 *
 *  written:       1988 09 20
 *                 1989 06 18
 *                 1990 01 21: Revision
 *                 1991 09 11: Revision
 *  latest update: 1997-01-06 10:54:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_fr_next ()
{
  ned_ws_find_replace_dialog (aw, 0);
}
