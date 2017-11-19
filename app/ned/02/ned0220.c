/*
 *  FILE %ned/02/ned0220.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:59:36
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
void p_wdwAup ()
{
  if (oper_level >= LEV_WDW
      || aw->ay < 1
      || (aw->box_type > 0 && aw->ay <= 2)
     ) return;

  aw->ay--;
  aw->cy--;
  aw->w_upd |= 0x05;
  ned_display_window (aw);
}
