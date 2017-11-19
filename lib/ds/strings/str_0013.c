/*
 *  FILE ~/usr/sbr/str_0013.c
 *
 *  written:       1990 11 26
 *                 1992 09 13: revision
 *  latest update: 1994-12-31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int upper_case (int n)
{
  switch (n)
  {
#ifdef MSDOS
    case 0x0087: n = 0x0080; break;    /* € <- ‡ */
    case 0x0084: n = 0x008E; break;    /* Ž <- „ */
    case 0x0086: n = 0x008F; break;    /*  <- † */
    case 0x0080: n = 0x0090; break;    /*  <- ‚ */
    case 0x0091: n = 0x0092; break;    /* ’ <- ‘ */
    case 0x0094: n = 0x0099; break;    /* ™ <- ” */
    case 0x0081: n = 0x009A; break;    /* š <-  */
    case 0x00A4: n = 0x00A5; break;    /* ¥ <- ¤ */
#endif
    default:
      if (n >= 'a' && n <= 'z') n = (n - 'a' + 'A');
      break;
  }

  return n;
}
