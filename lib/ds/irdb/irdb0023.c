/*
 *  FILE %ds/irdb/irdb0023.c
 *
 *  irrelational database
 *  - load an irdb handle from the file at current position
 *
 *  written:       1996-04-27
 *  latest update: 1996-04-27 13:47:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
char *irdb_load_string (FILE *fi, char *buffer, int bsize)
{
  int buffer_allocated= 0;
  int ch;
  int bpos= 0;
  char *rv;

  if (fi == (FILE *) 0) return (char *) 0;

  if (buffer == (char *) 0)
  {
    if (bsize <= 0) bsize= 128;
    if ((buffer= malloc (bsize)) == (char *) 0) return (char *) 0;
    buffer_allocated= 1;
  }

  while (bsize > 1)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi) || ch == 0) break;
    buffer [bpos++]= (char) ch;
  }
  buffer [bpos]= 0;

  rv= strdup (buffer);
  if (buffer_allocated) free_or_what (buffer);
  return rv;
}
