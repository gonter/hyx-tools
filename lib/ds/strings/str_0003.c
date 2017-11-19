/*
 *  FILE /usr/sbr/str_0003.c
 *
 *  1989 10 14: (aus STRINGS.SAR)
 *  1992 09 13: revision
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/asc2ebc.inc>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strcmp_ebcdic (char *s1, char *s2)          /* z.Z. unvollstaendig      */
{
  int c1, c2;

  while (*s1 == *s2 && *s1)
  {
    s1++;
    s2++;
  }

  if ((c1= *s1 & 0x00FF) == (c2= *s2 & 0x00FF)) return 0;

  return ((CODE_ASCII_to_EBCDIC [c1] & 0x00FF) -
          (CODE_ASCII_to_EBCDIC [c2] & 0x00FF) < 0) ? -1 : 1;
}
