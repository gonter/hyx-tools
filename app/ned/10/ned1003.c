/*
 *  FILE ~/usr/ned/10/ned1003.c
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
#include <gg/maus.h>
#include "proto.h"

extern int maus_angeschlossen;

/* ------------------------------------------------------------------------ */
void look2_for_maus ()
{
  if (maus_angeschlossen)
  {
    maus_setposition (0, 8);
    maus_enable ();
  }
}
