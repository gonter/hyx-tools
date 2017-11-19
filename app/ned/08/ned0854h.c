/*
 *  FILE %ned/08/ned0854h.c
 *
 *  prompt for a logic link name and evaluate it
 *
 *  written:       1991 06 25
 *  latest update: 1996-11-03 17:40:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_logic_link ()
{
  char str [80];

  str [0]= 0;
  if (rd_str ("Logic Link Direction: ", str, 80) == -1) return;
  eval_logic_link (aw, str);
}
