/*
 *  FILE %ned/02/ned0223.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1996-03-16  0:40:14
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
void p_wdwArt ()
{
  if (oper_level >= LEV_WDW) return;
  if ((aw->bx - aw->ax) <= 3) return;

  aw->ax++;
  aw->cx++;

  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
