/*
 *  File %dpp/codes/cs201.c
 *
 *  written:       1992-12-30: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_convert_stream (FILE *fi, FILE *fo, long *table, long limit)
{
  long count= 0L;
  int ch;
  long tr;

  if (fi == (FILE *) 0 || fo == (FILE *) 0) return -1L;

  for (; limit > 0L; limit--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    tr= table [ch];
    if (tr >= 0L && tr < 256L)
    {
      count++;
      fputc ((int) tr, fo);
    }
  }

  return count;
}
