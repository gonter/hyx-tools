/*
 *  FILE ~/usr/ned/09/ned0914.c
 *
 *  Operationen mit dem SETUP-File
 *  o  Installation von Tastenkommandos
 *  o  Installation von Makros
 *  o  Installation von Maus Menu Eintraegen
 *  Makroprozessor
 *  Jour File Prozessor
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *                 1991 06 01: Revision
 *  latest update: 1997-10-26 11:13:55
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern FILE *jou;
extern int pfx;

/* ------------------------------------------------------------------------ */
int jou_in ()
{
  int kv;

  kv= fgetc (jou) & 0x00FF;

  if (feof (jou))
  {
    p_close_jou ();
    return q_kbin ();
  }

  if (kv == 0)
  {
    pfx= P_FUNCT;
    kv= fgetc (jou) & 0x00FF;
  }

  return kv;
}
