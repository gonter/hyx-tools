/*
 *  FILE %ned/06/ned0608.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *                 1991 05 22: Revision
 *  latest update: 1995-09-26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;

/* ------------------------------------------------------------------------ */
void q_pushpage (struct WINDOWCTRL *w, int new_page)
{
  if (w == (struct WINDOWCTRL *) 0 || new_page < 0 || new_page > 7) return;
  akt_page= w->page= new_page;
  w_selpage (new_page);
  w->w_upd |= 0x05;
}
