/*
 *  FILE %ned/04/ned0414.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1997-01-12 16:46:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_save_restart ()
{
  /* Restart Info Schreiben */
  q_save_restart ();
  q_allsave (1);
  setcup (aw);
}
