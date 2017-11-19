/*
 *  File %dpp/codes/cs202.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1996-04-11 12:44:02
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/codes.h>

#ifndef MSDOS
#include <unistd.h>
#endif

static char *_tmpfile= "$$cs202$.$$";

/* ------------------------------------------------------------------------ */
int cs_convert_file (char *fni, char *fno, long *table)
{
  FILE *fi;
  FILE *fo;
  int rv= 0;

  if (fni == (char *) 0
      || *fni == 0
      || table == (long *) 0
     ) return -1;

  if ((fi= fopen (fni, "rb")) == (FILE *) 0) return -1;

  if (strcmp (fno, "-") == 0)
       fo= stdout;
  else fo= fopen ((fno == (char *) 0 || *fno == 0) ? _tmpfile : fno, "wb");

  if (fo == (FILE *) 0)
  {
    rv= -1;
    goto ERR;
  }

  cs_convert_stream (fi, fo, table, 0x7FFFFFF0);

  if (fo != stdout) fclose (fo);
ERR:
  fclose (fi);

  if (rv == 0 && (fno == (char *) 0 || *fno == 0))
  {
    unlink (fni);
    rename (_tmpfile, fni);
  }

  return rv;
}
