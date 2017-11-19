/*
 *  FILE ~/usr/sbr/str_0014.c
 *
 *  written:       1991 01 27: aus str_0002.c abgeleitet
 *                 1992 09 13: revision
 *  latest update: 1994-11-23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strcmp_cre (char *s1, char *s2)
{
  int idx1, idx2;
  int c1, c2;
  int skip;

  if (s1 == (char *) 0 || s2 == (char *) 0)
  {
    if (s1 != (char *) 0) return -1;
    if (s2 != (char *) 0) return  1;
    return 0;
  }

  idx1= idx2= 0;
  while ((c1= s1 [idx1] & 0x00FF) &&
         (c2= s2 [idx2] & 0x00FF))
  {
    switch (c1)
    {
#ifdef MSDOS
      case 0x0080: c1 = 0x0087; break;    /* € -> ‡ */
      case 0x008E: c1 = 0x0084; break;    /* Ž -> „ */
      case 0x008F: c1 = 0x0086; break;    /*  -> † */
      case 0x0090: c1 = 0x0082; break;    /*  -> ‚ */
      case 0x0092: c1 = 0x0091; break;    /* ’ -> ‘ */
      case 0x0099: c1 = 0x0094; break;    /* ™ -> ” */
      case 0x009A: c1 = 0x0081; break;    /* š ->  */
      case 0x00A5: c1 = 0x00A4; break;    /* ¥ -> ¤ */
#endif /* MSDOS */
      case 'R': case 'r':
        if ((skip= skip_re (&s1 [idx1])) > 0)
        {
          idx1 += skip;
          continue;
        }
      default:
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
        break;
    }

    switch (c2)
    {
#ifdef MSDOS
      case 0x0080: c2 = 0x0087; break;    /* € -> ‡ */
      case 0x008E: c2 = 0x0084; break;    /* Ž -> „ */
      case 0x008F: c2 = 0x0086; break;    /*  -> † */
      case 0x0090: c2 = 0x0082; break;    /*  -> ‚ */
      case 0x0092: c2 = 0x0091; break;    /* ’ -> ‘ */
      case 0x0099: c2 = 0x0094; break;    /* ™ -> ” */
      case 0x009A: c2 = 0x0081; break;    /* š ->  */
      case 0x00A5: c2 = 0x00A4; break;    /* ¥ -> ¤ */
#endif /* MSDOS */
      case 'R': case 'r':
        skip = skip_re (&s2 [idx2]);
        if (skip > 0)
        {
          idx2 += skip;
          continue;
        }
      default:
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
        break;
    }

    if (c1 != c2) return (c1 - c2 < 0) ? -1 : 1;

    idx1++;
    idx2++;
  }

  return (s1 [idx1] - s2 [idx2] < 0) ? -1 : 0;
}
