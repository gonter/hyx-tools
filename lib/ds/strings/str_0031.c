/*
 *  FILE %ds/strings/str_0031.c
 *
 *  written:       1994-05-20 (extracted from ~/usr/mail/distmail.c)
 *  latest update: 1999-09-10  3:37:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int enter_value (char *s, int pos, int val, int digits)
{
  int xpos;
  int v;

  if (val == -1)
  {
    for (; digits > 0; digits--) s [pos++]= 'X';
    return 0;
  }

  for (xpos= pos+digits-1; digits > 0; digits--)
  {
    v= val%10;
    val= val/10;
    s [xpos--]= (char) (v+'0');
  }

  return 1;
}
