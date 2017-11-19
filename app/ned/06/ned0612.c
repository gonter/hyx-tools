/*
 *  FILE %ned/06/ned0612.c
 *
 *  abort a file and close the window
 *
 *  written:       1987 04 08
 *  latest update: 2001-02-12  0:28:46
 *  $Id: ned0612.c,v 1.2 2001/02/12 00:03:31 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_wdwqfile ()
{
  if (oper_level >= LEV_FNM) return;
  p_abandon  ();
  ned_close_window ();
}

