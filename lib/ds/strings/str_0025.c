/*
 *  FILE ~/usr/sbr/str_0025.c
 *
 *  written:       1993-12-05
 *  latest update: 1993-12-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int strdiff (char *diff, char *s1, char *s2,
int eq_char, int diff_char, int eos_char)
{
  int cnt= 0;

  while (*s1 && *s2)
  {
    *diff= (char) ((*s1 == *s2) ? eq_char : diff_char);

    cnt++;
    diff++;
    s1++;
    s2++;
  }

  if (*s1 == 0 && *s2 == 0) goto DONE;

  *diff++= (char) eos_char;
DONE:
  *diff= 0;
  return cnt;
}
