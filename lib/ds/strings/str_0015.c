/*
 *  FILE ~/usr/sbr/str_0015.c
 *
 *  written:       1991 01 27
 *                 1992 09 13: revision
 *  latest update: 1994-11-23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int skip_re (char *str)
{
  if ((str [0] == 'R' || str [0] == 'r') &&
      (str [1] == 'E' || str [1] == 'e') &&
       str [2] == ':')
  {
    int idx= 3;

    while (str [idx] == ' ' || str [idx] == '\t') idx++;
    return idx;
  }

  return 0;
}
