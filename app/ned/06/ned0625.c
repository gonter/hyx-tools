/*
 *  FILE %ned/06/ned0625.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1991 09 03
 *  latest update: 1996-09-29 18:22:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int act_window_num;

/* ------------------------------------------------------------------------ */
int q2_jmpwdw (struct WINDOWCTRL *w)    /* Sprung ins Window                */
{
  if (get_window_number (w) == -1)
     return -1;         /* apparently not a valid window */

  aw= w;
  winstack_push (aw);

  return 0;
}
