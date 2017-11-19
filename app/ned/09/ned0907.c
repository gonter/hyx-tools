/*
 *  FILE %ned/09/ned0907.c
 *
 *  ** OBSOLETE **
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
 *  latest update: 1997-10-26 11:13:39
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/keys.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void stp_func (
FILE *fi,
int tn,                 /* Table Nummer   */
int f)                  /* Flag           */
{
  int pr_num;
  int knum= 0;

  f= 0;

  for (;;)
  {
    fscanf (fi, "%s", cmd);
    if (feof (fi)) break;
    if (cmd [0] == '#')
    {
      trash_until_eol (fi);
      continue;
    }
    if (ned_what_stp_cmd (cmd) >= 0) break;

    /* Code der eingegebenen Taste ermitteln */
    knum = identify_key (cmd);

    if (knum == 0) knum= (int) get_parameter_value (cmd);
    knum %= 256;

    for (;;)
    {
      fscanf (fi, "%s", cmd);
      if (feof (fi)) return;
      if (cmd [0] == '#') continue;
      if (ned_what_stp_cmd (cmd) >= 0) return;
      break;
    }
    pr_num= stp_whatprim (cmd);
    if (pr_num < 0) continue;
    P_TBL [tn*256+ knum] = CT2 [pr_num];
  }
}

