/*
 *  FILE %ned/02/ned0215b.c
 *
 *  create a feature window
 *
 *  written:       1995-09-23
 *  latest update: 1999-04-25 16:29:56
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

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *ned_create_feature_window ()
{
  register struct WINDOWCTRL *wc;

  if ((wc= wdw_alloc ()) != (struct WINDOWCTRL *) 0)
  {
    wdw_rst (wc);
    wc->page= -1;
  }

  return wc;
}
