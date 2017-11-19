/*
 *  FILE %ds/hyxta/hyxta006.c
 *
 *  written:       1994-03-30: extracted from %ds/hyxta/hyxta005.c
 *  latest update: 1996-12-22 18:30:06
 *
 */

#include <stdio.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
long hyx_ta_parse_stream (
struct HYX_PARSER_CLASS *hpc,
struct HYX_PARSER_STATUS *hps,
FILE *fi,
long max_to_read)
{
  int ch;
  int segment_ready;
  long bytes_read= 0L;
  struct TEXT_ELEMENT *ta_text_element= (struct TEXT_ELEMENT *) 0;

  hps->HPS_last_cat_code= -1;

  while (max_to_read-- > 0L)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;
    bytes_read++;

    ta_text_element= (struct TEXT_ELEMENT *) 0;
    segment_ready= hyx_ta_parse_char (hps, ch, &ta_text_element);

    if (segment_ready < 0) break;
    if (segment_ready == 1) hyx_ta_store_node (hpc, hps, ta_text_element);
  }

  ta_text_element= (struct TEXT_ELEMENT *) 0;

  segment_ready= hyx_ta_parse_flush (hpc, hps, &ta_text_element);
  if (segment_ready == 1) hyx_ta_store_node (hpc, hps, ta_text_element);

  return bytes_read;
}
