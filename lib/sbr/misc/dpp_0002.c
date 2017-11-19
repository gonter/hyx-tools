/*
 *  FILE %sbr/dpp_0002.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbchern
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *                 1991 12 11: rename /usr/nl_kr/lib/lut_0006.c
 *                             to     /usr/sbr/dpp_0002.c
 *  latest update: 1996-04-27 12:32:05
 *  $Id: dpp_0002.c,v 1.2 2005/09/04 20:27:37 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/dpp.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dpp_fwrite_long (FILE *fo, long val, int bytes)
{
  int i;
  unsigned char b[4];

  for (i= 3; i>=0; i--)
  {
    b[i]= (char) (val & 0x000000FFL);
    val= val >> 8;
  }

  return fwrite (&b[4-bytes], bytes, 1, fo);
}
