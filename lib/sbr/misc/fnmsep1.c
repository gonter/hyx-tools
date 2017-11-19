/*
 *  FILE %sbr/fnmsep1.c
 *
 *  index of last character of path name;
 *  i+1 == first char of filename
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1992 02 07: FILE %ned/04/ned0419.c copied ...
 *  latest update: 1995-11-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef __GG_CMS__
#include <gg/filename.h>
#endif

/* ------------------------------------------------------------------------ */
int isolate_path (char *s)
{
  int i= -1;
  int j;
  int ch;

  for (j= 0; (ch= s [j] & 0x00FF) != 0; j++)
    if (ch == '/'
#ifdef MSDOS
        || ch == '\\'
        || ch == ':'
#endif /* MSDOS */
       ) i= j;

  return i;
}
