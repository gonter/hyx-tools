/*
 *  FILE /usr/sbr/str_0108.c
 *
 *  1989 10 14: (aus STRINGS.SAR)
 *  1992 09 13: revision
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void strndel (char *str, int lng, int pos, int cnt)
{
  int i;

  for (i = pos + cnt; i < lng; i++)
      str [i-cnt] = str [i];
}
