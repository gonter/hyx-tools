/*
 *  FILE ~/usr/nl_kr/lib/nl_00301.c
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
int lmd_TWF (struct LMDT_CONTROL *lmdt, char *w)/* Test Word; Suche auf FILE*/
{
  long wi;
  int rv, lng;
  int i;
  int ch;
  int flg= 0;                   /* 1 -> wildcard                            */

  for (i= 0;; i++)
  {
    ch= w[i] & 0x00FF;
    lmdt->LMDT_ext_pattern [i]= (char) ch;
    if (ch == '*' || ch == '?')
    {
      w [i]= 0;
      flg= 1;
    }
    if (ch == 0) break;
  }

  if (lmdt->LMDT_LUT_FILE == (FILE *) 0)
  {
    rv= lookup_char (lmdt->LMDT_LUT, w, &wi, &lng);
  }
  else
  {
    fseek (lmdt->LMDT_LUT_FILE, 0L, 0);
    rv= lookup_file (lmdt->LMDT_LUT_FILE, w, &wi, &lng);
  }

  if (flg) printf ("set match pattern '%s'\n", lmdt->LMDT_ext_pattern);
  else lmdt->LMDT_ext_pattern [0]= 0;

  lmd_report (lmdt, w, rv, lng, wi);

  return 0;
}
