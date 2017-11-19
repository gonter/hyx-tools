/*
 *  FILE ~/usr/nl_kr/lib/nl_00304.c
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
int lmd_report (struct LMDT_CONTROL *lmdt, char *w, int rv, int lng, long wi)
{
  int i;
  char *cp;
  long dump_beg;
  long dump_end;

  if (rv < 0)
  { 
    fprintf (stderr, "ERROR: %d; w=%s\n", rv, w);
    if (*w == 0 && *lmdt->LMDT_ext_pattern)
    {
      lmdt->LMDT_pfx= "";
      lmdt->LMDT_rep2_cnt= 0;
      fseek (lmdt->LMDT_LUT_FILE, 0L, 0);
      printf ("weitere Worte:\n");
      lut_process_block (lmdt->LMDT_LUT_FILE, lmd_report2, lmdt);
    }
    return 0;
  }
  else
  if (rv == LOOKUP_not_found)
  {
    printf ("%s nicht gefunden\n", w);
    return 0;
  }
  else
  {
    if (lmdt->LMDT_LUT_FILE == (FILE *) 0)
    {
      cp= lut_char_get_word_buffer ();
      dump_beg= (long) lut_char_get_dump_beg ();
      dump_end= (long) lut_char_get_dump_end ();
    }
    else
    {
      cp= lut_file_get_word_buffer ();
      dump_beg= lut_file_get_dump_beg ();
      dump_end= lut_file_get_dump_end ();
    }

    printf ("cp='%s'\n", cp);
    printf ("beg=0x%08lX end=0x%08lX\n", dump_beg, dump_end);

    if ((rv & LOOKUP_found) /* && lmdt->LMDT_LUT_FILE == (FILE *) 0*/)
    {
      printf ("         Wort: %s -> WI=%8lX\n", w, wi);
      lmd_report_tfb (lmdt, wi);
    }

    if (rv == LOOKUP_prefix)
    {
      printf ("kuerzeres Wort: ");
      for (i= 0; i < lng; i++) fputc (w [i], stdout);
      printf (" -> WI=%8lX\n", wi);
      lmdt->LMDT_rep2_cnt= 0;
      lmdt->LMDT_pfx= "";
      lmd_report2 (cp, wi, (void *) lmdt);
    }

    if (rv & LOOKUP_prefix_3)
    {
      printf ("laengeres Wort: %s -> WI=%8lX\n", cp, wi);
      lmdt->LMDT_rep2_cnt= 0;
      lmdt->LMDT_pfx= "";
      lmd_report2 (cp, wi, (void *) lmdt);
    }

    if (rv & LOOKUP_prefix_4)
    {
      printf ("mehrere Worte die mit '%s\' beginnen. (%s)\n", w, cp);
    }

    if (lmdt->LMDT_LUT_FILE != (FILE *) 0
       && (((rv & LOOKUP_prefix_4) && *lmdt->LMDT_ext_pattern)
          ||(rv & LOOKUP_found)))
    {
      long doff;

      lmdt->LMDT_pfx= cp;
      lmdt->LMDT_rep2_cnt= 0;
      if ((doff= lut_file_get_dump_beg ()) >= 0L)
      {
        fseek (lmdt->LMDT_LUT_FILE, doff, 0);
        printf ("weitere Worte:\n");
        lut_process_block (lmdt->LMDT_LUT_FILE, lmd_report2, lmdt);
      }
    }

    return 1;
  }

  return 0;
}
