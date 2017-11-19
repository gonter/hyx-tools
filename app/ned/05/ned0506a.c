/*
 *  FILE %ned/05/ned0506a.c
 *
 *  get the number of lines to the top of the file
 *  first line := 1
 *
 *  written:       1987 04 08
 *                 1991 06 01: Revision
 *  latest update: 1996-05-26 11:34:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* Zeilennummer einer Zeile berechnen: ------------------------------------ */
int ned_cnt_line_2beg (register struct LINE *a)
{
  register int lin= 0;

  for (; a != (struct LINE *) 0; a= a->prev) lin++;

  return lin;
}
