/*
 *  FILE %ned/02/ned0241.c
 *
 *  vi emulation: append at end of line
 *
 *  written:       1993-07-31
 *  latest update: 1996-05-23 14:51:05
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_append_eol ()
{
  ned_jmp_eoln ();
  vi_ins ();
}
