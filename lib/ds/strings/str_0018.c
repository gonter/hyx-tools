/*
 *  FILE %ds/strings/str_0018.c
 *
 *  written:       1992 12 08
 *  latest update: 1996-05-06 10:36:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *rotate13 (char *s)
{
  int ch;
  char *x;

  if (s == (char *) 0) return (char *) 0;

  for (x= s; ch= (*x) & 0x00FF; x++)
  {
    if (ch >= 'a' && ch <= 'm') ch= ch+13; else
    if (ch >= 'n' && ch <= 'z') ch= ch-13; else
    if (ch >= 'A' && ch <= 'M') ch= ch+13; else
    if (ch >= 'N' && ch <= 'Z') ch= ch-13;
    *x = (char) ch;
  }

  return s;
}
