/*
 *  FILE %sbr/ftrans08.c
 *
 *  Transfer some range of a disk file to another.
 *  The file is opened, the transfer initiated and then closed again.
 *
 *  written:       1994-10-31: cloned from f2transfer
 *  latest update: 1996-10-12 12:10:12
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long f2transfer_crlf (char *fi_nm, FILE *fo, long cpy_start, long cpy_size)
{
  long rc;
  FILE *fi;

  if ((fi= fopen (fi_nm, "rb")) == (FILE *) 0) return -1L;

  if (cpy_start > 0L) fseek (fi, cpy_start, 0);
  rc= ftransfer_crlf (fi, fo, cpy_size);
  fclose (fi);

  return rc;
}
