/*
 *  FILE ~/usr/sbr/str_0012.c
 *
 *  written:       1990 11 26
 *                 1992 09 13: revision
 *  latest update: 1995-07-16
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int lower_case (int n)
{
  switch (n)
  {
#ifdef MSDOS
    case 0x0080: n = 0x0087; break;    /* € -> ‡ */
    case 0x008E: n = 0x0084; break;    /* Ž -> „ */
    case 0x008F: n = 0x0086; break;    /*  -> † */
    case 0x0090: n = 0x0082; break;    /*  -> ‚ */
    case 0x0092: n = 0x0091; break;    /* ’ -> ‘ */
    case 0x0099: n = 0x0094; break;    /* ™ -> ” */
    case 0x009A: n = 0x0081; break;    /* š ->  */
    case 0x00A5: n = 0x00A4; break;    /* ¥ -> ¤ */
#endif /* MSDOS */
    default:
      if (n >= 'A' && n <= 'Z') n = (n - 'A' + 'a');
      break;
  }

  return n;
}
