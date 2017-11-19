/*
 *  FILE ~/usr/sbr/str_0005.c
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1990 11 23: alle uebersetzbaren Zeichen werden behandelt
 *                 1992 09 13: revision
 *                 1993-03-03: CMS adaption
 *  latest update: 1995-03-18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *to_upper (char *n)
{
  int i, c;

  if (n == (char *) 0) return (char *) 0;

#ifndef __CMS__
  for (i= 0; (c= (n [i] & 0x00FF)) != 0; i++)
    if (c >= 'a' && c <= 'z')
      n [i] = (char) (c - 'a' + 'A');
#ifdef MSDOS
    else
      switch (c)
      { /* this applies only to the PC (MSDOS)! */
        case 0x0087: n [i] = (char) 0x0080; break;    /* € <- ‡ */
        case 0x0084: n [i] = (char) 0x008E; break;    /* Ž <- „ */
        case 0x0086: n [i] = (char) 0x008F; break;    /*  <- † */
        case 0x0080: n [i] = (char) 0x0090; break;    /*  <- ‚ */
        case 0x0091: n [i] = (char) 0x0092; break;    /* ’ <- ‘ */
        case 0x0094: n [i] = (char) 0x0099; break;    /* ™ <- ” */
        case 0x0081: n [i] = (char) 0x009A; break;    /* š <-  */
        case 0x00A4: n [i] = (char) 0x00A5; break;    /* ¥ <- ¤ */
      }
#endif /* MSDOS */
#else
  for (i= 0; c= n [i] & 0x00FF; i++)
    if ((c >= 'a' && c <= 'i')
      ||(c >= 'j' && c <= 'r')
      ||(c >= 's' && c <= 'z'))
      n [i] = (char) (c - 'a' + 'A');
#endif

  return n;
}
