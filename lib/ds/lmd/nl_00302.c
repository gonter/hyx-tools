/*
 *  FILE ~/usr/nl_kr/lib/nl_00302.c
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
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>
#include <gg/fileio.h>
#include <gg/sbr.h>
#include <gg/filename.h>

/* ------------------------------------------------------------------------ */
int lmd_report_tfb (struct LMDT_CONTROL *lmdt, long inf)
{
  if (lmdt->LMDT_TFB_FILE == (FILE *) 0) return 0;
  fseek (lmdt->LMDT_TFB_FILE, inf-1L, 0);
  printf ("[%d] TFB: ", lmdt->LMDT_rep2_cnt);
  ftransfer_line (lmdt->LMDT_TFB_FILE, stdout, 0x7FFFFFFFL);
  return 0;
}
