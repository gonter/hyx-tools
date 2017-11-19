/*
 *  FILE %ned/06/ned0606.c
 *
 *  jump to the window number i
 *  window numbers are in the range 1 .. n
 *
 *  written:       1987 04 08
 *                 1991 05 22: Revision
 *  latest update: 1997-01-12 16:15:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *q_jmpwdw (int k)
{
  for (aw= windows; --k && aw->next != (struct WINDOWCTRL *) 0; aw= aw->next);

  winstack_push (aw);
  q0_jmpwdw (aw);

  return aw;
}
