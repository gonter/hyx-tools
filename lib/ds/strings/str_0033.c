/*
 *  FILE %ds/strings/str_0033.c
 *
 *  set values into a character table
 *
 *  written:       1994-08-06
 *  latest update: 1996-09-03 13:17:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int chr_index (char *chars, int value)
{
  int i;
  int ch;

  if (chars == (char *) 0) return -1;

  for (i= 0; (ch= (*chars++) & 0x00FF) != 0; i++)
    if (value == ch) return i;

  return -1;
}
