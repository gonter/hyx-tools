/*
 *  File %dpp/codes/cs110.c
 *
 *  CS_ET8: entity translation functions
 *
 *  written:       1995-12-10: g.gonter@ieee.org
 *  latest update: 1997-10-24 12:09:48
 *
 */

#include <stdio.h>
#include <gg/fileio.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
long cs_et8_encode (
struct CS_ET8 *et8,
char *fni,
char *fno,
long cpy_size)
{
  FILE *fi;
  FILE *fo;
  int fi_opened= 0;
  int fo_opened= 0;
  long fsiz= 0L;

  FXOPEN (fni, fi, stdin,  "rb", fi_opened);
  FXOPEN (fno, fo, stdout, "wb", fo_opened);

  fsiz= cs_et8_ftransfer (et8, fi, fo, cpy_size);

  FXCLOSE (fi, fi_opened);
  FXCLOSE (fo, fo_opened);

  return 0;
}
