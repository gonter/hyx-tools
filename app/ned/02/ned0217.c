/*
 *  FILE %ned/02/ned0217.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 06 25: Revision
 *  latest update: 1997-10-26 10:59:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;
extern int NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void p_wdwXdn ()
{
  if (oper_level >= LEV_WDW
      || aw->by >= NED_TEXT_MAX_Y-1
     ) return;

  aw->ay++;
  aw->by++;
  aw->cy++;

  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
