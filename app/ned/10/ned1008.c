/*
 *  FILE %ned/10/ned1008.c
 *
 *  Maus Steuerung
 *
 *  written:       1991 02 03
 *                 1991 05 27: Revision
 *  latest update: 1995-12-31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_window_menu ()
{
  int wn;

  wn= q_window_menu ();
  if (wn >= 0) q_jmpwdw (wn);
}
