/*
 *  FILE %ned/05/ned0519.c
 *
 *  Zeile relativ zu ihrer Position im Window anspringen
 *
 *  written:       1991 06 02
 *  latest update: 1996-09-07 10:11:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int jmpline_relative (
register struct WINDOWCTRL *w,
double fraction)                /* Zielzeile relativ zum Window             */
{
  long dlines;                  /* Zahl der Zeilen im Window                */
  long xlines;                  /* Zahl der Zeilen im File                  */
  int alnr;                     /* errechnete absolute Zeilennummer         */

  dlines= (long) (w->by - w->ay + 1);
  xlines= (long) ned_cnt_total_lines (w->WC_act);

  alnr= (int) (fraction * xlines);
  if (alnr < 0) alnr= 0;

  return ned_jmp_2line_by_nr (w, alnr, 0x01);
}
