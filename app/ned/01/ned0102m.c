/*
 *  FILE %ned/01/ned0102m.c
 *
 *  move cursor to mid of screen
 *
 *  written:       1997-01-05
 *  latest update: 2001-02-11 11:56:31
 *  $Id: ned0102m.c,v 1.2 2001/02/12 00:03:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_vi_cursor_mid ()
{
  int where;
  struct WINDOWCTRL *w;

  if ((w= aw) == (struct WINDOWCTRL *) 0) return;

  where= (w->by - w->ay) / 2 + w->ay - w->cy;

  if (where < 0) ned_w_cursor_up (w, -where);
  if (where > 0) ned_w_cursor_down (w, where);

  vi_wc_jmp_boln (w);
}
