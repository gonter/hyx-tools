/*
 *  FILE %ned/02/ned0211.c
 *
 *  close a window
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1991 06 02: Revision
 *  latest update: 1999-04-25 16:29:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

#ifdef WINSTACK
extern struct PLIST *winstack;
#endif

extern struct WINDOWCTRL *windows;
extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_close_window ()         /* aktuelles Window killen  */
{
  if (oper_level >= LEV_LINK || ned_w_close_window (aw)) return;

#ifdef WINSTACK
  aw= (winstack != (struct PLIST *) 0
       && winstack->PL_val != (void *) 0
      )
      ? winstack->PL_val : windows;
#else
  aw= windows;
#endif

  q2_jmpwdw (aw);
  p_refresh_all ();
}
