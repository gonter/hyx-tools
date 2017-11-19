/*
 *  FILE ~/usr/ds/hyxp/hyxp0022.c
 *
 *  written:       1995-07-02
 *  latest update: 1995-07-02
 *
 */

#include <string.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_parse_string (
struct HYX_PARSER_STATUS *lps,
char *string)
{
  return hyx_parse_block (lps, string, (long) strlen (string));
}
