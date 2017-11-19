/*
 *  FILE %ned/04/ned0413.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1997-01-05 17:11:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_qabandon ()
{
  if (get_confirmation (CNF_panic, 0) <= 0) return;
  p_exit ();
}
