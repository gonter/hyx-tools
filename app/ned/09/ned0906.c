/*
 *  FILE %ned/09/ned0906.c
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
 *  latest update: 1997-10-26 11:13:31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void stp_rtbl (
FILE *fi,
int tn,                 /* Table Nummer   */
int f)                  /* Flag           */
{
  int pr_num;
  int tbl_off;
  int s_char;           /* 1 -> Sonderzeichen; z.b. ^O+    */

  f= 0;                 /* ####### */

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
    s_char = 0;
    if (cmd [0] >= 'a' || cmd [0] <= 'z') tbl_off = cmd [0] - 'a'+1; else
    if (cmd [0] >= 'A' || cmd [0] <= 'Z') tbl_off = cmd [0] - 'A'+1;
    if (cmd [0] >= '0' || cmd [0] <= '9')
    {
      tbl_off= (int) get_parameter_value (cmd);
      s_char= 1;
    }
    else
    {
      tbl_off = cmd [0];
      s_char = 1;
    }

    for (;;)
    {
      fscanf (fi, "%s", cmd);
      if (feof (fi)) return;
      if (cmd [0] == '#') continue;
      if (ned_what_stp_cmd (cmd) >= 0) return;
      break;
    }

    pr_num = stp_whatprim (cmd);
    trans_str (cmd, cmd, 9999);
    if (pr_num < 0) continue;

    if (s_char || tn == 0 /* Standardtable: Nur CTRL erlaubt!!! */)
      P_TBL [tn*256+ tbl_off      ] = CT2 [pr_num];
    else
    {
      P_TBL [tn*256+ tbl_off      ] = CT2 [pr_num];
      P_TBL [tn*256+ tbl_off+'a'-1] = CT2 [pr_num];
      P_TBL [tn*256+ tbl_off+'A'-1] = CT2 [pr_num];
    }
  }
}
