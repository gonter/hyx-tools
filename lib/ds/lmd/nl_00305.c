/*
 *  FILE ~/usr/nl_kr/lib/nl_00305.c
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
int lmd_RL3 (                   /* Read Look Up Table                       */
struct LMDT_CONTROL *lmdt,
char *fn,                       /* name of LUT to read                      */
int mode)                       /* 0 -> RAM; sonst -> FILE                  */
{
  long lng;
  char *t_fn;

  if (fn == (char *) 0
     || *fn == 0
     || (t_fn= translate_logic_filename (fn)) == (char *) 0)
    return -1;

  if (*t_fn == 0) t_fn= strdup (fn); /* well, this should be done by trans */
  printf (">>> RL3: fn=%s t_fn=%s\n", fn, t_fn);

  lmdt->LMDT_LUT_FILE= (FILE *) 0;

  if (lmdt->LMDT_LUT != (char *) 0)
  {
    free (lmdt->LMDT_LUT);
    lmdt->LMDT_LUT= (char *) 0;
  }

  if (mode != 0)
  {
    printf (((lmdt->LMDT_LUT_FILE= fopen (t_fn, "rb")) == (FILE *) 0)
            ? "error opening LUT file %s (%s)\n"
            : "LUT %s (%s) fuer FILE-Test eroeffnet\n",
            fn, t_fn);

    return 0;
  }

#ifndef __CMS__
/* LUT in memory is not supported for CMS ... */
#ifdef MSDOS
#define MAX_LUT 65000L
#else
#define MAX_LUT 6500000L
#endif

  if ((lng= read_file2buffer (&lmdt->LMDT_LUT, t_fn, MAX_LUT)) <= 0L)
  {
    printf ("error reading LUT file %s (%s)\n", fn, t_fn);
    return -1;
  }
  printf ("LUT file size: %ld bytes\n", lng);
  lmdt->LMDT_LUT_FILE= (FILE *) 0;
#endif /* __CMS__ */

  free (t_fn);
  return 0;
}
