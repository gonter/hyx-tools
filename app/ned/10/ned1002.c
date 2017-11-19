/*
 *  FILE ~/usr/ned/10/ned1002.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1994-07-09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include <gg/maus.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
extern int maus_angeschlossen;
extern int W_TEXT_CELL_X;
extern int W_TEXT_CELL_Y;
extern int W_TEXT_MAX_X;
extern int W_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void look1_for_maus ()
{
  maus_setup ();
  maus_angeschlossen= maus_reset ();
  if (maus_angeschlossen == -1) maus_angeschlossen = 0;
  else
  {
    maus_set_y_margins (0, W_TEXT_MAX_Y*W_TEXT_CELL_Y-1);
    maus_set_x_margins (0, W_TEXT_MAX_X*W_TEXT_CELL_X-1);
  }
}
