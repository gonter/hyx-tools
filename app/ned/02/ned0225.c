/*
 *  FILE %ned/02/ned0225.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:59:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;
extern int NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void p_wdwBdn ()
{
  if (oper_level >= LEV_WDW) return;
  if (aw->by >= NED_TEXT_MAX_Y-1) return;

  aw->by++;
  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
