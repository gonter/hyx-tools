/*
 *  FILE %ta/ta015.c
 *
 *  written:       1994-11-12
 *  latest update: 1996-12-22 20:49:43
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/attlist.h>
#include <gg/parse.h>
#include <gg/ta.h>

/* ------------------------------------------------------------------------ */
int hyx_ta_print_text_segments (FILE *fo, struct TEXT_SEGMENT *ts)
{
  for (;
       ts != (struct TEXT_SEGMENT *) 0;
       ts= ts->TSEG_next)
  {
    /* fputc ('[', fo); */
    /*****************
    sgml_write_data (fo, "", "",
                     ts->TSEG_text_array, (int) ts->TSEG_text_lng);
    *****************/
    fputs (ts->TSEG_text_array, fo);
    /* fputc (']', fo); */
  }

  return 0;
}
