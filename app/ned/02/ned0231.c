/*
 *  FILE %ned/02/ned0231.c
 *
 *  Window oeffnen und linken
 *
 *  written:       1991 05 30
 *  latest update: 1996-05-28 20:04:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_clone_window ()
{
  struct WINDOWCTRL *w_old;

  w_old= aw;                            /* remember the previous window     */
  p_wdwopen ();
  q2_link (aw, w_old, NEDJMP_FLAG_REDRAW);
  ned_display_window (aw);
}
