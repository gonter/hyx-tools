/*
 *  FILE %ned/02/ned0258.c
 *
 *  vi emulation: go down one line and place cursor at first no-blank char
 *
 *  written:       1993-07-31
 *  latest update: 1996-12-19 21:52:00
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_jmp_next_boln ()
{
  ned_cursor_down ();
  vi_jmp_boln ();
}
