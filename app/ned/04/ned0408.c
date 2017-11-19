/*
 *  FILE %ned/04/ned0408.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1996-01-06 11:27:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_sx ()                            /* ^K X: Save ALL Windows and Exit  */
{
  if (oper_level < LEV_SEXIT)           /* Abspeichern nicht immer          */
     if (q_allsave (1) != 1) return;    /* erlaubt; sonst nur EXIT          */
  p_exit ();
}
