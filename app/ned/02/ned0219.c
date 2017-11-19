/*
 *  FILE %ned/02/ned0219.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 09 15: Revision
 *  latest update: 1996-03-16  1:27:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int oper_level;
extern int NED_TEXT_MAX_X;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_wdwXrt ()
{
  if (oper_level >= LEV_WDW) return;
  if (aw->bx >= NED_TEXT_MAX_X-1) return;

  aw->ax++;
  aw->bx++;
  aw->cx++;
  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
