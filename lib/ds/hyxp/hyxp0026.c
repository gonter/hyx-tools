/*
 *  FILE %ds/hyxp/hyxp0026.c
 *
 *  add character to text segment buffer
 *
 *  written:       1995-12-21
 *  latest update: 1995-12-21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/parse.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_parser_add_char (
struct HYX_PARSER_STATUS *lps,
int ch)
{
  if (lps == (struct HYX_PARSER_STATUS *) 0) return -1;

  lps->HPS_segment [lps->HPS_segment_length++]= (char) ch;
  lps->HPS_segment [lps->HPS_segment_length]= 0;

  if (lps->HPS_segment_length >= MAX_SEGMENT_LENGTH)
    hyx_parser_finish_segment (lps);

  return 0;
}
