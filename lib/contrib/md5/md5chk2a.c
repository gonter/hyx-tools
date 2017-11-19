/*
 *  FILE ~/usr/contrib/md5/md5chk2a.c
 *
 *  return a MD5 digest block for a given array of memory blocks
 *  see also MD5chk2_block ()
 *
 *  written:       1995-05-10
 *  latest update: 1995-05-10
 *
 */

#include <string.h>
#include <contrib/global.h>
#include <contrib/md5.h>
#include <contrib/md5gg.h>

static unsigned char digest [16]; /* message digest */

/* ------------------------------------------------------------------------ */
unsigned char *MD5chk2_block_array (
unsigned char *str [],
int lng [],
int cnt)
{
  MD5_CTX context;
  unsigned char *cp;
  int i;
  int l;

  MD5Init (&context);
  for (i= 0; i < cnt; i++)
  {
    if ((cp= str [i]) == (unsigned char *) 0 || (l= lng [i]) == 0) break;
    MD5Update (&context, cp, l);
  }
  MD5Final (digest, &context);

  return digest;
}
