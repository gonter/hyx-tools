/*
 *  FILE %ned/01/ned0102v.c
 *
 *  move cursor to top of screen
 *
 *  written:       1996-12-19
 *  latest update: 2001-02-11 11:57:38
 *  $Id: ned0102v.c,v 1.3 2001/02/12 00:03:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int repeat;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_vi_cursor_top ()
{
  struct WINDOWCTRL *w;
  int idx;

  if ((w= aw) == (struct WINDOWCTRL *) 0) return;

  idx= w->cy - w->ay - repeat;
  if (idx < 0)
  {
    ned_w_cursor_down (w, -idx); /* BUG here: don't scroll! */
  }
  else ned_w_cursor_up (w, idx);
  vi_wc_jmp_boln (w);
}
