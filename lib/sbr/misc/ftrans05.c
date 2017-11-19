/*
 *  FILE %sbr/ftrans05.c
 *
 *  Transfer some range of a disk file to another.
 *  The file is opened, the transfer initiated and then closed again.
 *
 *  written:       1994-07-23: extracted from %usr/utl/shar.c
 *  latest update: 1995-09-10
 *
 */

#include <stdio.h>
#include <gg/sbr.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long f5transfer_to_shar (
char *fi_nm,
FILE *SHAR,
char *fnm,
long cpy_start,
long cpy_size,
char *fi_buf,
int shar_bufsiz,
char *st_dat_buffer)
{
  long rc;
  FILE *fi;

  if ((fi= fopen (fi_nm, "rb")) == (FILE *) 0) return -1L;
  setvbuf (fi, fi_buf, _IOFBF, shar_bufsiz);

  if (cpy_start > 0L) fseek (fi, cpy_start, 0);
  rc= ftransfer_to_shar (fi, SHAR, fnm, cpy_size, st_dat_buffer);
  fclose (fi);

  return rc;
}
