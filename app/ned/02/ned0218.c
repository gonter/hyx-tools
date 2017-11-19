/*
 *  FILE %ned/02/ned0218.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 06 25: Revision
 *  latest update: 1997-10-26 10:59:34
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

/* ------------------------------------------------------------------------ */
void p_wdwXlt ()
{
  if (oper_level >= LEV_WDW
      || aw->ax <= 0
     ) return;

  aw->ax--;
  aw->bx--;
  aw->cx--;

  aw->w_upd |= 0x05;

  ned_display_window (aw);
}
