/*
 *  FILE ~/usr/sbr/str_0009.c
 *
 *  String Compare, unsigned Characters
 *
 *  written:       1990 07 14: aus c:/usr/utl/merge.c
 *                 1992 09 13: revision
 *  latest update: 1995-02-12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strcmp_us (char *s1, char *s2)
{
  if (s1 == (char *) 0 || s2 == (char *) 0)
  {
    if (s1 != (char *) 0) return -1;
    if (s2 != (char *) 0) return  1;

    return 0;
  }

  while (*s1 == *s2 && *s1)
  {
    s1++;
    s2++;
  }

  if (*s1 == *s2) return  0;
  if (*s1 == 0)   return -1;
  if (*s2 == 0)   return  1;

  return  (((*s1 & 0x00FF) - (*s2 & 0x00FF)) < 0) ? -1 : 1;
}
