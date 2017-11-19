/*
 *  FILE ~/usr/sbr/str_0010.c
 *
 *  String Compare, weighted Characters
 *
 *  written:       1990 11 23
 *                 1992 09 13: revision
 *  latest update: 1995-05-13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef MSDOS
#ifndef cdecl
#define cdecl
#endif

#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strcmp_weighted (char *s1, char *s2)
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

  return  ((get_weight_code (*s1 & 0x00FF)
            - get_weight_code (*s2 & 0x00FF)) < 0) ? -1 : 1;
}
