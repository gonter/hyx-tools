/*
 *  FILE ~/usr/ned/03/ned0326.c
 *
 *  written:       1987 08 19
 *                 1991 01 29: Revision
 *                 1991 05 26: Revision
 *  latest update: 1994-12-28
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
void wd_init (struct WINDOWCTRL *w)
{
  if (akt_page != w->page)
     w_selpage (akt_page= w->page);
}
