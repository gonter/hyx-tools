/*
 *  FILE %ned/06/ned0629.c
 *
 *  renumber all windows and return number of the given window
 *
 *  The window specified as the parameter can be (struct WINDOWCTRL *) 0,
 *  this will effectively renumber all windows
 *
 *  written:       1994-05-23
 *  latest update: 1996-07-26  3:32:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int get_window_number (struct WINDOWCTRL *w)
{
  int num= 1;
  int rv= -1;
  struct WINDOWCTRL *wc;

  for (wc= windows; wc != (struct WINDOWCTRL *) 0; wc= wc->WC_next)
  {
    if (wc == w) rv= num;
    wc->wc_window_number= num++;
  }

  return rv;
}
