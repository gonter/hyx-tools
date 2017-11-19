/*
 *  FILE ~/usr/nl_kr/lib/nl_00306.c
 *
 *  Datenkapsel
 *  - Funktionen zum Ueberpruefen von Worten in einer LUT
 *
 *  written:       1989 03 29
 *                 1990 02 14: Revision
 *                 1994-12-19: isolated from wordcr03.c
 *  latest update: 1995-07-16
 *
 */


#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_RL3_set_tfb_file (struct LMDT_CONTROL *lmdt, char *fn)
{
  return ((lmdt->LMDT_TFB_FILE= fopen (fn, "rb")) == (FILE *) 0);
}
