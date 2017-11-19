/*
 *  FILE ~/usr/ned/09/ned0913.c
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
 *  latest update: 1994-12-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <stdio.h>
#include <gg/keys.h>
#include "proto.h"

extern FILE *jou;

/* Editoreingabe: --------------------------------------------------------- */
int kbin_jou ()
{
  int kv;

  kv= kbin ();

  if (kv & 0x0100)
  {
    kv &= 0x00FF;
    fputc (0x00, jou);  /* Variante 2 !!!! */
  }

  fputc (kv, jou);

  return kv & 0x00FF;
}
