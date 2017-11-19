/*
 *  FILE %sbr/fclosec.c
 *
 *  written:       1995-11-05
 *  latest update: 1995-11-05
 *
 */

#include <stdio.h>
#include <gg/fileio.h>

/* ------------------------------------------------------------------------ */
int fclose_or_what (FILE *f)
{
  if (f != (FILE *) 0) fclose (f);
  return 0;
}
