/*
 *  FILE %sgml/chksgml2.c
 *
 *  check SGML files
 *
 *  written:       1991 07 14
 *                 1992 12 07: revision; extra buffers
 *                 1993-01-03: entity lookup via code table
 *                 1994-12-10: chksgml3.c isolated from here
 *  latest update: 1999-04-24 11:59:29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/filename.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int chksgml_file (
FILE *fo,
FILE *fo_report,
char *fn,
int verbose_level,
long byte_offset,
long byte_count,
int flags)
{
  FILE *fi;
  char *afn;
  int rv;
  char *xbuffer= (char *) 0;
#define XBUFFER_SIZE 4096

  if ((afn= translate_logic_filename (fn)) == (char *) 0) afn= fn;

  if (verbose_level > 0) printf ("CHKSGML: Testing %s (%s)\n", afn, fn);

  if ((fi= fopen (afn, "rb")) == (FILE *) 0)
  {
    if (verbose_level > 0) printf ("- not opened!\n");
    return -2;
  }

  if ((xbuffer= malloc (XBUFFER_SIZE)) != (char *) 0)
    setvbuf (fi, xbuffer, _IOFBF, XBUFFER_SIZE);

  fseek (fi, byte_offset, 0);

  rv= chksgml_stream (fo, fo_report, fi, fn, verbose_level,
                      byte_offset, byte_count, flags);
  fclose (fi);

  if (xbuffer != (char *) 0) free (xbuffer);

  return rv;
}
