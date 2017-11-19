/*
 *  FILE %ned/11/ned1103.c
 *
 *  Such- und Ersetzungsfunktionen
 *
 *  written:       1988 09 20
 *                 1989 06 18
 *                 1991 09 11: Revision
 *  latest update: 1997-01-06 10:54:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_replace ()
{
  ned_ws_find_replace_dialog (aw, 2);
}
