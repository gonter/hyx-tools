/*
 *  FILE %ds/strings/str_0004.c
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1990 11 23: Revision, all translatable characters
 *                             are converted
 *                 1992 09 13: revision
 *                 1993-03-03: CMS adaption
 *  latest update: 1995-11-26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *to_lower (char *n)
{
  int i, c;

  if (n == (char *) 0) return (char *) 0;

#ifndef __CMS__
  for (i = 0; (c= n [i] & 0x00FF) != 0; i++)
    if (c >= 'A' && c <= 'Z')
      n [i]= (char) (c - 'A' + 'a');
#ifdef MSDOS
    else
      switch (c)
      { /* This applies only to the PC (MSDOS)! */
        case 0x0080: n [i] = (char) 0x0087; break;    /* € -> ‡ */
        case 0x008E: n [i] = (char) 0x0084; break;    /* Ž -> „ */
        case 0x008F: n [i] = (char) 0x0086; break;    /*  -> † */
        case 0x0090: n [i] = (char) 0x0082; break;    /*  -> ‚ */
        case 0x0092: n [i] = (char) 0x0091; break;    /* ’ -> ‘ */
        case 0x0099: n [i] = (char) 0x0094; break;    /* ™ -> ” */
        case 0x009A: n [i] = (char) 0x0081; break;    /* š ->  */
        case 0x00A5: n [i] = (char) 0x00A4; break;    /* ¥ -> ¤ */
      }
#endif /* MSDOS */
#else
  for (i = 0; c = n [i] & 0x00FF; i++)
    if ((c >= 'A' && c <= 'I')
      ||(c >= 'J' && c <= 'R')
      ||(c >= 'S' && c <= 'Z'))
      n [i]= (char) (c - 'A' + 'a');
#endif

  return n;
}
