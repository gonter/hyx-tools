/*
 *  FILE %lexicon/parse014.c
 *
 *  written:       1991 03 27
 *  latest update: 1995-08-21
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int key_string_transform (char *s, int lng)
{
  int rv= 0;
  int ch1, ch2;
  int i;

  if (s == (char *) 0) return -1;

  for (i= 0; i < lng && (ch1= *s & 0x00FF) != 0; i++, s++)
  {
    ch2= lower_case (ch1);
    if (ch1 != ch2)
    {
      if (rv == 0) rv= 1;
      *s= (char) ch2;
    }
  }

  return rv;
}
