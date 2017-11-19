/*
 *  FILE %ds/irdb/irdb0004.c
 *
 *  irrelational database
 *
 *  written:       1996-04-05
 *  latest update: 1996-08-08 17:35:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
long irdb_dump_string (
FILE *fo,
char *s)
{
  long rc= 0;

  if (s != (char *) 0) rc= (long) fputs (s, fo);
  fputc (0x00, fo);
  rc++;

  return rc;
}
