/*
 *  FILE ~/usr/ned/08/ned0856.c
 *
 *  written:       1991 06 25
 *  latest update: 1994-04-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int akt_buttons;

/* ------------------------------------------------------------------------ */
void p_logic_link_menu ()
{
  if (akt_buttons & LL_menu) eval_logic_link (aw, "menu"); else
  if (akt_buttons & LL_more) p_logic_link_more (); else
  p_link_more ();
}
