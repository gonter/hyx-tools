/*
 *  FILE ~/usr/sbr/hex2bin.c
 *
 *  convert a printable hex string into a binary data block
 *  see also:
 *  - bin2hex.c int bin_to_hex (char *bin, char *hex, int lng)
 *              convert a binary data block into a printable hex string
 *
 *  written:       1993-12-05: <Gerhard.Gonter@wu-wien.ac.at>
 *                 1995-02-20: renamed from md5s2b.c to hex2bin.c
 *  latest update: 1995-08-04
 *
 */

#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int hex_to_bin (char *hex, char *bin, int lng)
{
  int i= 0;
  int ch;
  int v= 0;

  if (lng <= 0) return -1;

  while (lng-- > 0)
  {
    ch= *hex++ & 0x00FF;
    if (ch >= '0' && ch <= '9') ch= ch - '0'; else
    if (ch >= 'a' && ch <= 'f') ch= ch - 'a' + 10; else
    if (ch >= 'A' && ch <= 'F') ch= ch - 'A' + 10; else
    return -1;

    if (i%2)
      *bin++ = (char) (v+ch);
    else v= 16*ch;
    i++;
  }

  return 0;
}
