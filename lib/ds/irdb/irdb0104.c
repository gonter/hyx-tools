/*
 *  FILE %ds/irdb/irdb0104.c
 *
 *  irrelational database
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 13:05:58
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_diag_string (
FILE *fo,
char *s)
{
  long rc= 0;

  fputc ('\'', fo);
  if (s != (char *) 0) rc= (long) fputs (s, fo);
  fputc ('\'', fo);
  rc++;

  return rc;
}
