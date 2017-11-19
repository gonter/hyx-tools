/*
 *  FILE %ned/02/ned0242.c
 *
 *  vi emulation: append at end begin of line
 *
 *  written:       1993-07-31
 *  latest update: 1996-05-23 20:13:32
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_insert_bol ()
{
  vi_jmp_boln ();
  vi_ins ();
}
