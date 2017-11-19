/*
 *  FILE %ds/strings/str_0028.c
 *
 *  locate n-th word in a string
 *
 *  written:       1994-02-04
 *  latest update: 1997-11-09 11:14:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
char *locate_word (char *s, int num)
{
  int ch;

  if (s != (char *) 0)
    for (; *s && num >= 0; num--)
    {
      for (; (ch= *s) && (ch == ' ' || ch == '\t'); s++);
      if (num == 0) return s;
      for (; (ch= *s) && ch != ' ' && ch != '\t'; s++);
    }

  return (char *) 0;
}
