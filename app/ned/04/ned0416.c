/*
 *  FILE %ned/04/ned0416.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1992 01 01: revision
 *  latest update: 1997-10-26 10:52:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_shell ()
{
  if (oper_level >= LEV_SPECIAL) return;
  q_shell ((char *) 0);
}
