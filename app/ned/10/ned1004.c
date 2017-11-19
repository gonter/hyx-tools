/*
 *  FILE %ned/10/ned1004.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1997-10-26 10:22:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include <gg/maus.h>
#include "proto.h"

extern int W_TEXT_CELL_X;
extern int W_TEXT_CELL_Y;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void maus_wdw (int where)   /* Groesse des aktuellen Windows aendern        */
{
  int x, y, t;
  int ox, oy;
  int w_text_cell_x;
  int w_text_cell_y;

  w_text_cell_x = W_TEXT_CELL_X;
  w_text_cell_y = W_TEXT_CELL_Y;

  for (;;)
  {
    maus_position (&x, &y, &t);
    if (!(t & 0x02)) break;
  }

  switch (where)
  {
    case  1: /* links oben */
             ox = aw->ax; oy = aw->ay;
             aw->ax = x/w_text_cell_x + 1;
             aw->ay = y/w_text_cell_y + 1;
             if (aw->bx-aw->ax <= 3) aw->ax = aw->bx-4;
             if (aw->by-aw->ay <= 3) aw->ay = aw->by-4;
             if (aw->ay < 1) aw->ay = 1;
             aw->cx += aw->ax-ox;
             aw->cy += aw->ay-oy;
             break;
    case  2: /* rechts oben */
             oy = aw->ay;
             aw->bx = x/w_text_cell_x -1;
             aw->ay = y/w_text_cell_y +1;
             if (aw->bx-aw->ax <= 3) aw->bx = aw->ax+4;
             if (aw->by-aw->ay <= 3) aw->ay = aw->by-4;
             if (aw->ay < 1) aw->ay = 1;
             aw->cy += aw->ay-oy;
             break;
    case  3: /* links unten */
             ox = aw->ax;
             aw->ax = x/w_text_cell_x +1;
             aw->by = y/w_text_cell_y -1;
             if (aw->bx-aw->ax <= 3) aw->ax = aw->bx-4;
             if (aw->by-aw->ay <= 3) aw->by = aw->ay+4;
             aw->cx += aw->ax-ox;
             break;
    case  4: /* rechts unten */
             aw->bx = x/w_text_cell_x -1;
             aw->by = y/w_text_cell_y -1;
             if (aw->bx-aw->ax <= 3) aw->bx = aw->ax+4;
             if (aw->by-aw->ay <= 3) aw->by = aw->ay+4;
             if (aw->ay < 1) aw->ay = 1;
             break;
  }

  maus_disable ();
  aw->w_upd |= 0x05;
  ned_display_window (aw);
}
