/*
 *  FILE ~/usr/sbr/trasheol.c
 *
 *  overread until end of line
 *
 *  written:       1992 07 20
 *  latest update: 1994-08-14
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
long trash_until_eol (FILE *fi)
{
  long ctr= 0L;

  while (!feof (fi) && (fgetc (fi) & 0x00FF) != 0x0A) ctr++;

  return ctr;
}
