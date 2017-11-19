/*
 *  FILE %ned/06/ned0603.c
 *
 *  Refresh Window (= redraw contents of window)
 *
 *  written:       1987 04 08
 *  latest update: 1996-03-16  1:46:30
 *  $Id: ned0603.c,v 1.3 2002/06/12 18:51:48 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_refresh ()
{
#ifdef W_MODEL_CURSES
  /*** curses_cls (); ***/
  clear ();
#endif
  aw->w_upd |= 0x04;
  ned_display_window (aw);
}
