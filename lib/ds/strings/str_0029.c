/*
 *  FILE ~/usr/sbr/str_0029.c
 *
 *  written:       1994-03-24
 *  latest update: 1994-12-22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
long count_char (int code, char *s, long size)
{
  long count= 0L;

  while (size-- > 0L) if (((int) (*s++ & 0x00FF)) == code) count++;

  return count;
}
