/*
 *  FILE ~/usr/ds/hyxp/hyxp0021.c
 *
 *  written:       1995-07-02
 *  latest update: 1995-07-02
 *
 */

#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_parse_block (
struct HYX_PARSER_STATUS *lps,
char *block,
long size)
{
  struct TEXT_ELEMENT *te;

  while (size-- > 0L)
    te= hyx_parse_char (lps, *block++ & 0x00FF);

  return te;
}
