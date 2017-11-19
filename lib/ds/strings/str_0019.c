/*
 *  FILE ~/usr/sbr/str_0019.c
 *
 *  find last occurance of char in string
 *
 *  written:       1993-01-15
 *  latest update: 1994-08-13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *strridx (char *s, int ch)
{
  int i;

  if (s == (char *) 0) return (char *) 0;

  for (i= strlen(s)-1; i>=0; i--)
    if (((int) (s[i] & 0x00FF)) == ch) return &s[i];

  return (char *) 0;
}
