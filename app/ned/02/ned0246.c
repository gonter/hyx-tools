/*
 *  FILE %ned/02/ned0246.c
 *
 *  vi emulation: insert after line
 *
 *  written:       1994-02-06
 *  latest update: 1996-05-23 14:51:44
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
void vi_insert_after_line ()
{
  vi_ins ();                    /* insert mode on                           */
  ned_jmp_eoln ();              /* goto end of line                         */
  p_nl ();                      /* insert new line and make it active       */
}
