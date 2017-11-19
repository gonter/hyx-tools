/*
 *  FILE %ned/02/ned0222.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 10:59:41
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
void p_wdwAlt ()
{
  if (oper_level >= LEV_WDW) return;
  if (aw->ax <= 0) return;
  aw->ax--; aw->cx--;
  aw->w_upd |= 0x05;
  ned_display_window (aw);
}
