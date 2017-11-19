/*
 *  FILE ~/usr/nl_kr/lib/nl_00303.c
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
int lmd_report2 (char *str, long inf, void *client_data)
{
  struct LMDT_CONTROL *lmdt;

  if ((lmdt= (struct LMDT_CONTROL *) client_data) == (void *) 0) return -1;

  sprintf (lmdt->LMDT_complete_key, "%s%s", lmdt->LMDT_pfx, str);
  if (lmdt->LMDT_ext_pattern [0] != 0 && match (lmdt->LMDT_ext_pattern, lmdt->LMDT_complete_key)
      <= 0) return 0;

  lmdt->LMDT_rep2_cnt++;
  printf ("[%d] INF: 0x%08lX %s\n", lmdt->LMDT_rep2_cnt, inf, lmdt->LMDT_complete_key);
  lmd_report_tfb (lmdt, inf);

  return 0;
}
