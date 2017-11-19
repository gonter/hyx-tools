/*
 *  FILE %ned/06/ned0607.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *                 1991 05 22: Revision
 *  latest update: 1997-10-26 10:25:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;
extern ned_input_handler *nextchar;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_pushpage ()       /* ^OP 1..9 */
{
  int k;

  if (oper_level >= LEV_WDW) return;
  k= (*nextchar) ();
  if (k < '0' || k > '7') return;
  q_pushpage (aw, k-'0');
  wda_setup ();
}

