/*
 *  FILE %ned/02/ned0212.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 09 03: Revision
 *  latest update: 1997-10-26 11:11:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;

/* ------------------------------------------------------------------------ */
int p_wdwopen ()
{
  int win_num;
  struct WINDOWCTRL *wc;

  if (oper_level >= LEV_LINK) return -1;

  q_wdwopen (&wc, &win_num);
  q2_jmpwdw (wc);
  q0_jmpwdw (wc);

  return win_num;
}
