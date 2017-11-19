/*
 *  FILE ~/usr/contrib/md5/md5chks.c
 *
 *  return the md5 digest string for a given input string
 *
 *  written:       1994-06-24
 *  latest update: 1995-02-20
 *
 */

#include <string.h>
#include <contrib/md5gg.h>

/* ------------------------------------------------------------------------ */
unsigned char *MD5chk2_string (unsigned char *str)
{
  return MD5chk2_block (str, strlen (str));
}
