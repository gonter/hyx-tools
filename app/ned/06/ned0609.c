/*
 *  FILE %ned/06/ned0609.c
 *
 *  jump to the window at the given mouse coordinates
 *
 *  written:       1987 04 08
 *                 1991 05 22: Revision
 *  latest update: 1997-01-12 16:30:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern struct PLIST *winstack;

/* ------------------------------------------------------------------------ */
int maus_jmpwdw (int x, int y)
{
  register struct WINDOWCTRL *awc;      /* Refresh Screen */
  register struct PLIST *pl;

  for (pl= winstack;; pl= pl->PL_lnk)
  {
    if (pl == (struct PLIST *) 0) return 0;
    if ((awc= (struct WINDOWCTRL *) pl->PL_val) == (struct WINDOWCTRL *) 0)
      continue;
    if (x+1 >= awc->ax && x-1 <= awc->bx &&
        y+1 >= awc->ay && y-1 <= awc->by) break;
  }
  
  q2_jmpwdw (awc);
  q0_jmpwdw (awc);

  return 9999;
}
