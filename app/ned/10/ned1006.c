/*
 *  FILE ~/usr/ned/10/ned1006.c
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

/* ------------------------------------------------------------------------ */
void maus_menue (int mode)  /* Menueleiste(n) aktivieren                    */
{
  execute_mm_item (mm_maus_menu (mode, 1, 1));
  maus_enable ();
}
