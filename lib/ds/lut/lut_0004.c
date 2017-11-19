/*
 *  FILE ~/usr/nl_kr/lib/lut_0004.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbuechern
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *                 1994-07-31: lut_print_block isolted from this module
 *  latest update: 1994-12-19
 *
 */

/* #define DEBUG_001 */
/* #define DEBUG_002 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lut_print (
FILE *fo,                       /* Ausgabe File                             */
char *lut_name,                 /* Look Up Table                            */
char *format,                   /* Format der Informationsausgabe           */
long start)                     /* begin of the dump                        */
{
  FILE *lut;
  int rc;

  if ((lut= fopen (lut_name, "rb")) == (FILE *) 0) return -1;
  fseek (lut, start, 0);
  rc= lut_print_block (fo, lut, format);
  fclose (lut);

  return rc;
}
