/*
 *  File %dpp/codes/cs203.c
 *
 *  written:       1993-04-18: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_convert_string (char *str, long *table)
{
  long count= 0L;
  long tr;
  int ch;

  for (; (ch= (*str & 0x00FF)) != 0; str++)
  {
    tr= table [ch];
    if (tr >= 0L && tr < 256L)
    {
      count++;
      *str= (char) tr;
    }
  }

  return count;
}
