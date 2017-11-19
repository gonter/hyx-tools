/*
 *  FILE %ned/05/ned0510b.c
 *
 *  delete the current line in a window, no display
 *  see also: %ned/05/ned0510.c
 *
 *  written:       1987 04 08: as del_line
 *                 1991 02 07: Revision
 *                 1991 05 26: Revision
 *                 1994-12-27: extracted from ned0510.c
 *  latest update: 1996-10-05 10:07:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_delete_current_line (
register struct WINDOWCTRL *w)          /* current window                   */
/* return value:                                                            */
/* -1: didn't do anything                                                   */
/* bit 0: line was last on screen                                           */
/* bit 1: line was first on screen                                          */
{
  if (w == (struct WINDOWCTRL *) 0) return -1;

  return ned_delete_a_line (w, w->WC_act);
}
