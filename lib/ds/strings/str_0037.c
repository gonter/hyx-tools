/*
 *  FILE %ds/strings/str_0037.c
 *
 *  remove apostrophes from a character strings
 *
 *  written:       1994-12-31
 *  latest update: 1996-10-29 16:08:48
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int remove_apostrophe (char *s)
{
  char *d= s;

  while (*s) if (*s == '\'' || *s == '\"') s++; else *d++= *s++;

  return 0;
}
