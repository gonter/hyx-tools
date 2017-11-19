/*
 *  FILE %ned/05/ned0506b.c
 *
 *  get the number of lines to the bottom of the file
 *  last line := 1
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:26:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_cnt_line_2end (register struct LINE *p)
{
  register int cnt= 0;

  for (; p != (struct LINE *) 0; p= p->next) cnt++;

  return cnt;
}
