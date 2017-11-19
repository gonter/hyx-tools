/*
 *  FILE ~/usr/ned/10/ned1005.c
 *
 *  Maus Steuerung
 *
 *  written:       1988 09 04
 *                 1990 01 20: Modularisierung
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1995-04-29
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
void p_menue ()       /* Menueleiste(n) aktivieren */
{
#ifdef MSDOS
  execute_mm_item (mm_maus_menu (0, maus_angeschlossen, 1));
#endif
}
