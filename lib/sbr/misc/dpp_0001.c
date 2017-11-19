/*
 *  FILE %sbr/dpp_0001.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbchern
 *
 *  written:       1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *                             check_word       -> lookup_char
 *                             check_word_file  -> lookup_file
 *                 1990 01 20: zerlegt in Library-Module
 *                 1991 03 15: Revision; AIX
 *                 1991 12 11: mv %nl_kr/lib/lut_0005.c -> %sbr/dpp_0001.c
 *  latest update: 1995-07-02
 *  $Id: dpp_0001.c,v 1.2 2003/06/25 14:38:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/dpp.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long dpp_fread_long (FILE *fi, int bytes)
{
  long v;
  int i;

  v= 0L;

  for (i= 0; i < bytes; i++)
  {
    v= v*256L + ((long) (fgetc (fi) & 0x00FF));
    if (feof (fi)) return 0L;
  }

  return v;
}
