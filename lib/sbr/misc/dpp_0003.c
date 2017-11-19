/*
 *  FILE /usr/dpp/dpp_0003.c
 *
 *  Funktionen zum Durchsuchen von LUT-Woerterbchern
 *
 *  1989 06 11: aus WORDCR01.C isolierte Funktionen:
 *              check_word       -> lookup_char
 *              check_word_file  -> lookup_file
 *  1990 01 20: zerlegt in Library-Module
 *  1991 03 15: Revision; AIX
 *  1991 12 11: rename /usr/nl_kr/lib/lut_0003.c -> /usr/sbr/dpp_0003.c
 *  $Id: dpp_0003.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <gg/dpp.h>

#ifdef MSDOS
# pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long dpp_get_long (const char *buf, int bytes)
{
  long v;
  int i;

  v=0L;

  for (i=0;i<bytes;i++)
  {
    v = v*256L + ((long) (buf [i] & 0x00FF));
  }

  return v;
}

