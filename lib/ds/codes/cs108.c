/*
 *  File %dpp/codes/cs108.c
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
long cs_et8_fputs (struct CS_ET8 *et8, char *str, FILE *fo)
{
  int ch;
  long siz= 0L;

  if (str == (char *) 0) return -1;

  while (ch= (*str++) & 0x00FF) siz += cs_et8_fputc (et8, ch, fo);

  return siz;
}
