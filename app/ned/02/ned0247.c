/*
 *  FILE %ned/02/ned0247.c
 *
 *  vi emulation: insert before line
 *
 *  written:       1994-02-06
 *  latest update: 1999-09-12 22:31:20
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_insert_before_line ()
{
  vi_ins ();                    /* insert mode on                           */
  ned_jmp_boln ();              /* goto beginning of line                   */
  p_nl2 ();                     /* insert new line                          */
}
