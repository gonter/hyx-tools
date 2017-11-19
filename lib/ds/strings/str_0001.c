/*
 *  FILE %ds/strings/str_0001.c
 *
 *  copy string and strip blanks and tabs
 *
 *  written:       1989 10 14: (aus STRINGS.SAR)
 *                 1992 09 13: revision
 *  latest update: 1996-09-28 18:05:24
 *
 */

#ifdef MSDOS
#pragma  check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void strnscpy (         /* String Copy; Strip Blanks & TABS;                */
char *d,                /* destination                                      */
char *s,                /* source                                           */
int cnt)                /* maximal cnt Zeichen in Dest; d [cnt]=0;          */
{
  int blank= 0;
  int anything= 0;

  for (;;)
  switch (*s)
  {
    case 0x00: *d= 0; return;
    case 0x09:

    case 0x20:
      if (anything) blank= 1;
      s++;
      break;

    default:
      if (cnt - blank - 1 < 0)
      {
        *d= 0;
        return;
      }

      if (blank)
      {
        *d++= 0x20;
        cnt--;
        blank=0;
      }

      *d++= *s++;
      cnt--;
      anything= 1;
      break;
  }
}
