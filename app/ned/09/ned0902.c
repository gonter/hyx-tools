/*
 *  FILE %ned/09/ned0902.c
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
 *  latest update: 1996-07-13 20:45:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern char stp_fnm [];
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_edsetup ()
{
  if (oper_level >= LEV_STP) return;

  ned_open_file (stp_fnm, (char *) 0, (char *) 0, NED_OPENF_DEF_STP);
}

