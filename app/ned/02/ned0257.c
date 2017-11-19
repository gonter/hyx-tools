/*
 *  FILE %ned/02/ned0257.c
 *
 *  vi emulation: go up one line and place cursor at first no-blank char
 *
 *  written:       1993-07-31
 *  latest update: 1996-12-19 21:15:03
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_jmp_prev_boln ()
{
  ned_cursor_up ();
  vi_jmp_boln ();
}
