/*
 *  FILE %ned/04/ned0415.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1997-01-12 16:47:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_load_restart ()
{
  /* Restart Info Lesen                 */
  /* Files einlesen                     */
  /* Windows aufbauen+ Anzeige anpassen */

  q_load_restart ();
  p_rdsetup ();
  wda_setup ();
  setcup (aw);
}
