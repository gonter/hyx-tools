/*
 *  FILE %ds/strings/str_0034.c
 *
 *  change a character to another in a string
 *
 *  written:       1994-08-12
 *  latest update: 1996-08-11 14:34:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int xchange (char *str, int from, int to)
{
  int ch;

  for (; (ch= (*str & 0x00FF)) != 0; str++) if (ch == from) *str= (char) to;

  return 0;
}
