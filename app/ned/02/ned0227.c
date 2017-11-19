/*
 *  FILE %ned/02/ned0227.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:55:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;
extern int NED_TEXT_MAX_X;

/* ------------------------------------------------------------------------ */
void p_wdwBrt ()
{
  if (oper_level >= LEV_WDW) return;
  if (aw->bx >= NED_TEXT_MAX_X-1) return;

  aw->bx++;
  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
