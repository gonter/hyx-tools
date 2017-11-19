/*
 *  FILE %ned/09/ned0901.c
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
 *  latest update: 1997-10-26 11:12:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/strings.h>
#include "proto.h"

extern char stp_fnm [];

/* ------------------------------------------------------------------------ */
void def_setupfnm (char *s)
{
  strcpy_max (stp_fnm, s, MAX_FNM_LENGTH);
}
