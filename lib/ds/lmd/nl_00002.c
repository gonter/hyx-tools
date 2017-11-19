/*
 *  FILE %ds/lmd/nl_00002.c
 *
 *  nl_key_valid (w)
 *
 *  Pruefen, ob ein Wort als Schluessel verwendet werden kann
 *
 *  written:       1989 09 10
 *  latest update: 1996-12-22 12:40:53
 *  $Id: nl_00002.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lookup.h>

/* Pruefen, ob ein Wort als Schluessel verwendet werden kann. --------------- */
int nl_key_valid (const char *w)
/* RETURN:  0 .. ok; -1 .. w kann nicht als Key verwendet werden */
{
  int idx, ch;

  if (w == (char *) 0) return -1;

  for (idx= 0; (ch= w [idx] & 0x00FF) != 0; idx++)
      if (ch < 0x05 || ch == 0x00FF) return -1;

  if (idx == 0 ||                               /* Leerstring               */
      idx > MAX_LUT_KEY_LENGTH) return -1;      /* Wort zu lang             */

  return 0;
}
