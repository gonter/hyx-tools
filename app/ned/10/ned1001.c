/*
 *  FILE %ned/10/ned1001.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1997-10-26 10:22:50
 *  $Id: ned1001.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include <gg/maus.h>
#include <gg/keys.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
extern int W_TEXT_CELL_X;       /* Bildschirmgroesse    */
extern int W_TEXT_CELL_Y;

extern int MPflag;              /* Makro Prozessor Flag */
extern int maus_angeschlossen;
extern int jou_flag;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
int ned_check_mouse ()
{
  int x, y, t;

  if (!maus_angeschlossen) return (*nextchar) ();

  for (;;)
  {
    if (kbhit () || jou_flag == 2 || MPflag)
    {
      maus_disable ();
      return (*nextchar) ();
    }

    maus_position (&x, &y, &t);
    x /= W_TEXT_CELL_X;
    y /= W_TEXT_CELL_Y;

    switch (ned_mouse_event (x, y, t, 0, 0))
    {
      case 1:
      case 2: return -1;
    }
  }

  return -1;
}
