/*
 *  FILE %sbr/ftrans02.c
 *
 *  Transfer some range of a disk file to another.
 *  The file is opened, the transfer initiated and then closed again.
 *
 *  written:       1993-09-28
 *  latest update: 1996-12-03 22:27:22
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long f2transfer (char *fi_nm, FILE *fo, long cpy_start, long cpy_size)
{
  long rc;
  FILE *fi;

  if (strcmp ("-", fi_nm) == 0)
  {
    rc= ftransfer_del_dot (stdin, fo, cpy_size);
  }
  else
  {
    if ((fi= fopen (fi_nm, "rb")) == (FILE *) 0) return -1L;
    if (cpy_start > 0L) fseek (fi, cpy_start, 0);
    rc= ftransfer (fi, fo, cpy_size);
    fclose (fi);
  }

  return rc;
}
