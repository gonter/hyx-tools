/*
 *  FILE /usr/sbr/str_0011.c
 *
 *  String Compare, weighted Characters, without case
 *
 *  1990 11 23
 *  1992 09 13: revision
 *
 */

# ifdef MSDOS
# pragma  check_stack(off)
# endif
# ifndef MSDOS
# ifndef cdecl
# define cdecl
# endif
# endif

#include <gg/strings.h>

int cdecl get_weight_code (int code);

/* ------------------------------------------------------------------------ */
int strcmp_cweighted (char *s1, char *s2)
{
  int i, c1, c2;

  if (s1 == (char *) 0 || s2 == (char *) 0)
  {
    if (s1 != (char *) 0) return -1;
    if (s2 != (char *) 0) return  1;
    return 0;
  }

  for (i = 0; (c1 = s1 [i] & 0x00FF) &&
              (c2 = s2 [i] & 0x00FF); i++)
  {
    switch (c1)
    {
      case 0x0080: c1 = 0x0087; break;    /* € -> ‡ */
      case 0x008E: c1 = 0x0084; break;    /* Ž -> „ */
      case 0x008F: c1 = 0x0086; break;    /*  -> † */
      case 0x0090: c1 = 0x0082; break;    /*  -> ‚ */
      case 0x0092: c1 = 0x0091; break;    /* ’ -> ‘ */
      case 0x0099: c1 = 0x0094; break;    /* ™ -> ” */
      case 0x009A: c1 = 0x0081; break;    /* š ->  */
      case 0x00A5: c1 = 0x00A4; break;    /* ¥ -> ¤ */
      default : if (c1 >= 'A' && c1 <= 'Z')
                   c1 = c1 - 'A' + 'a';
                break;
    }

    switch (c2)
    {
      case 0x0080: c2 = 0x0087; break;    /* € -> ‡ */
      case 0x008E: c2 = 0x0084; break;    /* Ž -> „ */
      case 0x008F: c2 = 0x0086; break;    /*  -> † */
      case 0x0090: c2 = 0x0082; break;    /*  -> ‚ */
      case 0x0092: c2 = 0x0091; break;    /* ’ -> ‘ */
      case 0x0099: c2 = 0x0094; break;    /* ™ -> ” */
      case 0x009A: c2 = 0x0081; break;    /* š ->  */
      case 0x00A5: c2 = 0x00A4; break;    /* ¥ -> ¤ */
      default : if (c2 >= 'A' && c2 <= 'Z')
                   c2 = c2 - 'A' + 'a';
                break;
    }

    c1 = get_weight_code (c1);
    c2 = get_weight_code (c2);

    if (c1 != c2)
         return (c1 - c2 < 0) ? -1 : 1;
  }

  return (get_weight_code (s1 [i] & 0x00FF) 
          - get_weight_code (s2 [i] & 0x00FF) < 0) ? -1 : 0;
}
