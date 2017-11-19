/*
 *  FILE ~/usr/nl_kr/lib/nl_00001.c
 *
 *  nl_get_str (fi, s)
 *
 *  Wort-String aus einem File lesen
 *
 *  written:       1989 09 10
 *  latest update: 1995-04-01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>

/* ------------------------------------------------------------------------ */
int nl_get_str (
FILE *fi,
char *s)
{
  int ch;
  int cnt= 0;

  /* Spaces, Satzzeichen usw. ueberlesen */
  for (;;)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof(fi))
    {
      *s= 0;
      return cnt;
    }
    cnt++;

    if ((ch >=  'a' && ch <=  'z') ||
        (ch >=  'A' && ch <=  'Z') ||
        (ch >=  '0' && ch <=  '9') ||
         ch ==  '_' ||
        (ch >= 0x80 && ch <= 0xA5) ||   /* Umlaute, nationale Zeichen   */
        (ch >= 0xE0 && ch <= 0xEF))     /* Umlaute, griechische Zeichen */
      break;
  }

  /* Wort einlesen */
  for (;;)
  {
    *s++ = (char) ch;
    ch= fgetc (fi) & 0x00FF;
    if (feof(fi))
    {
      *s= 0;
      return cnt;
    }
    cnt++;

    if ((ch >=  'a' && ch <=  'z') ||
        (ch >=  'A' && ch <=  'Z') ||
        (ch >=  '0' && ch <=  '9') ||
         ch ==  '_'                ||
        (ch >= 0x80 && ch <= 0xA5) ||   /* Umlaute, nationale Zeichen   */
        (ch >= 0xE0 && ch <= 0xEF))     /* Umlaute, griechische Zeichen */
      continue;

    *s= 0;
    return cnt;
  }
}
