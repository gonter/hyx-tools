/*
 *  FILE %ned/03/ned0327.c
 *
 *  ========================================================
 *  Einlesen von Tastencodes und Behandlung der
 *  Funktionstasten
 *  ========================================================
 *  Dieses File wird nur unter MS_DOS benoetigt!
 *  Es ersetzt das File CONIO.S unter CPM68K.
 *  ========================================================
 *
 *  written:       1987 08 19
 *                 1989 08 15: Revision
 *                 1991 01 29: Revision
 *  latest update: 1997-09-07 12:57:22
 *  $Id: ned0327.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/keys.h>
#include "ed.h"
#include "proto.h"

extern int pfx;

/* ------------------------------------------------------------------------ */
int q_kbin ()
{
  int k;

  if ((k= kbin ()) == -1) return -1;

  if (k >= 0x0100) pfx= P_FUNCT;

  k &= 0x00FF;

  return k;
}
