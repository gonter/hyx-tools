/*
 *  File %dpp/codes/cs207.c
 *
 *  written:       1993-04-18: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_convert_block (char *str, long size, long *table)
{
  long count= 0L;
  long tr;
  int ch;

  for (; size > 0L; str++, size--)
  {
    ch= *str & 0x00FF;
    tr= table [ch];
    if (tr >= 0L && tr < 256L)
    {
      count++;
      *str= (char) tr;
    }
  }

  return count;
}
