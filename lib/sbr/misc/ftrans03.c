/*
 *  FILE %sbr/ftrans03.c
 *
 *  Transfer some range of a disk file to another.
 *  The file is opened, the transfer initiated and then closed again.
 *
 *  written:       1994-05-29
 *  latest update: 1996-10-12 12:07:59
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long f3transfer (char *fi_nm, char *fo_nm, long cpy_start, long cpy_size)
{
  long rc;
  FILE *fi;
  FILE *fo;

  if ((fi= fopen (fi_nm, "rb")) == (FILE *) 0) return -1L;
  if ((fo= fopen (fo_nm, "wb")) == (FILE *) 0)
  {
    fclose (fi);
    return -1L;
  }

  if (cpy_start > 0L) fseek (fi, cpy_start, 0);
  rc= ftransfer (fi, fo, cpy_size);
  fclose (fi);
  fclose (fo);

  return rc;
}
