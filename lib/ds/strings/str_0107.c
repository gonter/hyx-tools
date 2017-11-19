/*
 *  FILE %ds/strings/str_0107.c
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1992 09 13: revision
 *  latest update: 1995-12-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void strnins (char *str, int lng, int pos, int cnt)
{
  int i;

  for (i= lng-1; i >= pos; i--) str [i+cnt]= str [i];

  str [lng+cnt]= 0;
}
