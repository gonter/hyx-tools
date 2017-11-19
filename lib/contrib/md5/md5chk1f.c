/*
 *  FILE %contrib/md5/md5chk1f.c
 *
 *  return a MD5 digest block for a given block
 *
 *  written:       1995-09-01
 *  latest update: 1995-09-01
 *
 */

#include <stdio.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
unsigned char *MD5chk_file_block (char *fnm, long beg, long size)
{
  FILE *fi;
  unsigned char *digest;

  if (fnm == (char *) 0
      || *fnm == 0
      || (fi= fopen (fnm, "rb")) == (FILE *) 0
     ) return (unsigned char *) 0;

  fseek (fi, beg, 0);
  digest= MD5chk_stream (fi, size);
  fclose (fi);

  return digest;
}
