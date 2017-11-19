/*
 *  FILE ~/usr/contrib/md5/md5d2s.c
 *
 *  convert an MD5 digest string into a printable string
 *
 *  written:       1993-01-06: <Gerhard.Gonter@wu-wien.ac.at>
 *  latest update: 1995-04-01
 *
 */

#include <stdio.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
int MD5Digest2String (char *digest, char *string)
{
  int i;

  for (i= 0; i<16; i++)
  {
    sprintf (string, "%02x", *digest & 0x00FF);
    string += 2;
    digest++;
  }

  return 0;
}
