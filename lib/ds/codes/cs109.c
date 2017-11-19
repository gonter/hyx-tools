/*
 *  File %dpp/codes/cs109.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_et8_ftransfer (struct CS_ET8 *et8, FILE *fi, FILE *fo, long cpy_size)
{
  int ch;
  long fsiz= 0L;

  if (fi == (FILE *) 0 || fo == (FILE *) 0) return -1L;

  for (; cpy_size > 0L; cpy_size--)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    fsiz += cs_et8_fputc (et8, ch, fo);
  }

  return fsiz;
}
