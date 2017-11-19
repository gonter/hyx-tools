/*
 *  FILE ~/usr/ned/08/ned0832.c
 *
 *  Umschaltung in das File Format SGML
 *
 *  written:       1991 02 07
 *  latest update: 1994-04-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_format_SGML ()
{
  aw->file_format= FMT_SGML;
}
