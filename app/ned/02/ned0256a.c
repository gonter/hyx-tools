/*
 *  FILE %ned/02/ned0256a.c
 *
 *  vi emulation: place cursor at given column
 *  T2D: adjust horizontal view
 *
 *  written:       1997-09-07
 *  latest update: 1997-09-07 13:27:07
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

extern struct WINDOWCTRL *aw;
extern int repeat;

/* ------------------------------------------------------------------------ */
void vi_jmp_column ()
{
  int col;

  col= repeat-1;
  if (col < 0) col= 0;

  aw->cx= col - aw->hv + aw->ax;
}
