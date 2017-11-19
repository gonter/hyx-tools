/*
 *  FILE ~/usr/ned/01/ned0134.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void strfill (char *s, int cnt, int ch)
{
  while (cnt-- > 0) *s++= (char) ch;
}
