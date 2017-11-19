/*
 *  FILE %ned/09/ned0908.c
 *
 *  Operationen mit dem SETUP-File
 *  o  Installation von Makros
 *
 *  written:       1987 09 10
 *                 1989 04 23: Maus Menue Setup
 *                 1991 05 26: Revision
 *  latest update: 1996-12-04 18:19:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/sbr.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void stp_macro (FILE *fi, char *token, int max_token, int mac_type)
{
  int rc;

  for (;;)
  {
    rc= fread_line (fi, token, max_token);
    if (rc <= 0 && feof (fi)) break;
    if (token [0] == '#') continue;

    if (ned_what_stp_cmd (token) >= 0) break;
    mac_parse (token, mac_type);
  }
}
