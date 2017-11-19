/*
 *  FILE %ned/08/ned0814.c
 *
 *  return the currently active feature window, if really active
 *
 *  written:       1992 01 13
 *  latest update: 1996-03-15 14:46:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *active_feature_window (struct WINDOWCTRL *w)
{
  struct WINDOWCTRL *w_rv= (struct WINDOWCTRL *) 0;
  struct WINDOWCTRL *w2;
  int wn= 1;

  for (w2= windows; w2 != (struct WINDOWCTRL *) 0; w2= w2->WC_next)
  {
    w2->wc_window_number= wn++;
    if (w2->file_type == FTY_FTRWDW && w2->feature_window == w)
      w_rv= w2;
  }

  return w_rv;
}
