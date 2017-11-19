/*
 *  FILE ~/usr/contrib/md5/md5d2s.c
 *
 *  convert an printable MD5 string into digest format
 *
 *  written:       1993-12-05: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-02-20
 *
 */

#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
int MD5String2Digest (char *digest, char *string)
{
  int i;
  int ch;
  int v= 0;

  for (i= 0; i < 32; i++)
  {
    ch= *string++ & 0x00FF;
    if (ch >= '0' && ch <= '9') ch= ch - '0'; else
    if (ch >= 'a' && ch <= 'f') ch= ch - 'a' + 10; else
    if (ch >= 'A' && ch <= 'F') ch= ch - 'A' + 10; else
    return -1;
    if (i%2)
      *digest++ = (char) (v+ch);
    else v= 16*ch;
  }

  return 0;
}
