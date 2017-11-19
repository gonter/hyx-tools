/*
 *  FILE %ned/02/ned0226.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:59:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_wdwBlt ()
{
  if (oper_level >= LEV_WDW) return;
  if ((aw->bx - aw->ax) <= 3) return;

  aw->bx--;
  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
