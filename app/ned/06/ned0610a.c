/*
 *  FILE %ned/06/ned0610a.c
 *
 *  open a window and prompt for the file name
 *
 *  written:       1994-12-02
 *  latest update: 1996-05-25 10:00:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_ofile1 ()
{
  q_ofile (NED_OPENF_REDRAW | NED_OPENF_CONTEXT
           | NED_OPENF_HISTORY | NED_OPENF_PROMPT);
}
