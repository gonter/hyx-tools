/*
 *  FILE ~/usr/ned/08/ned0833.c
 *
 *  Umschaltung in das File Format ASCII
 *
 *  written:       1991 02 07
 *  latest update: 1994-07-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_format_ASCII ()
{
  aw->file_format= FMT_ASCII;
}
