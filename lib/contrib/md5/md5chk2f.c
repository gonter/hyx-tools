/*
 *  FILE %contrib/md5/md5chk2f.c
 *
 *  return a MD5 digest block for a given block
 *
 *  written:       1995-09-01
 *  latest update: 1995-09-01
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <contrib/global.h>
#include <contrib/md5.h>
#include <contrib/md5gg.h>

static unsigned char digest [16]; /* message digest */

#define BS 4096

/* ------------------------------------------------------------------------ */
unsigned char *MD5chk_stream (FILE *fi, long size)
{
  MD5_CTX context;
  char *block;
  int lng;

  if ((block= malloc (BS)) == (char *) 0) return (unsigned char *) 0;

  MD5Init (&context);
  while (size > 0L)
  {
    lng= (size > BS) ? BS : ((int) size);
    lng= fread (block, 1, lng, fi);
    if (lng <= 0) break;
    MD5Update (&context, block, lng);
  }
  MD5Final (digest, &context);

  return digest;
}
