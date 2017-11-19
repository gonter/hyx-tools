/*
 *  FILE %ned/09/ned0910.c
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
 *  latest update: 1997-10-26 11:12:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include <gg/maus.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include "message.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int stp_maus (FILE *fi)
{
  int status= 0;                /* status of line parser                    */
  int spalte= 0;                /* mouse menu column                        */
  int zeile= 0;                 /* mouse menu line                          */
  int pr_num= 0;                /* NED primitive command for menu item      */
  char *cp;                     /* token string duplicate string            */

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

    switch (status)
    {
      case 0: /* Spalten Nummer: 0 .. 9 */
        spalte= (int) get_parameter_value (cmd)-1;
        status++;
        break;
      case 1: /* Zeilen Nummer 0 .. ?? */
              zeile= (int) get_parameter_value (cmd);
              status++;
              break;
      case 2: /* Verbundenens Primitive */
              pr_num= stp_whatprim (cmd);
              /* pr_num == -1 -> unbekanntes Primitive;         */
              /*                 das ist jedoch erlaubt!        */
              status++;
      case 3: /* String im Menu */
        fscanf (fi, "%[ \t]", cmd);
        fscanf (fi, "%[^\n]", cmd);
        if (feof (fi)) break; fgetc (fi);
        if ((cp= strdup (cmd)) == (char *) 0)
        {
          ned_error_message (ERR_MEMORY);
          return -1;
        }
        if (spalte >= 0 && zeile >= 0)
          mm_install_function (spalte, zeile, cp,
                               (pr_num<0) ? -1L : (long) CT2 [pr_num],
                               0, 2);
        status= 0;
        break;
    }
  }

  return 0;
}
