/*
 *  FILE %ned/06/ned0611.c
 *
 *  save a file and close the window   *OBSOLETE*
 *
 *  written:       1987 04 08
 *  latest update: 1996-05-26 22:00:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_wdwsfile ()
{
  if (oper_level >= LEV_FNM) return;
  p_ssave ();
  ned_close_window ();
}
