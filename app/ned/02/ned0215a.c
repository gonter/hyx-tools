/*
 *  FILE %ned/02/ned0215a.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 29: Revision
 *  latest update: 1999-04-25 16:29:47
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
struct WINDOWCTRL *ned_create_editor_window ()
{
  register struct WINDOWCTRL *wc;

  if ((wc= wdw_alloc ()) != (struct WINDOWCTRL *) 0
      && ned_window_size (wc, DEFAULT_WDW_MODE, 0) == 0
     )
  {
    wdw_rst (wc);
  }

  return wc;
}
