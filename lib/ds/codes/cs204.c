/*
 *  File %dpp/codes/cs204.c
 *
 *  translate a string according to a character-to-string table
 *
 *  written:       1993-06-11: g.gonter@ieee.org
 *  latest update: 1994-10-02
 *
 */

#include <string.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_string_tlate (
char *dst,
char *src,
int dst_siz,
struct CS_tlate_table *tt)
{
  int ch;
  int l;
  char *s;

  while ((ch= *src++ & 0x00FF) != (char) 0)
  {
    s= tt->CStt_table [ch];
    l= strlen (s);
    if (l > dst_siz) return -1;
    strcpy (dst, s);
    dst= dst+l;
    dst_siz -= l;
  }

  return 0;
}
