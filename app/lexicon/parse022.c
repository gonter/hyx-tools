/*
 *  FILE ~/usr/lexicon/parse022.c
 *
 *  Text Segment Liste ausgeben
 *
 *  written:       1994-11-16
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dump_text_segment_list (FILE *fo, struct TEXT_SEGMENT *ts)
{
  long l;
  char *cp;
  int first_char= -1;

  if (ts != (struct TEXT_SEGMENT *) 0)
  {
    cp= ts->TSEG_text_array;
    first_char= *cp;
    goto PRINT_SEGMENT;
  }

  while (ts != (void *) 0)
  {
    cp= ts->TSEG_text_array;
PRINT_SEGMENT:
    fputc ('|', fo);
    for (l= ts->TSEG_text_lng; l > 0; l--) fputc (*cp++, fo);
    if ((ts= ts->TSEG_next) == (struct TEXT_SEGMENT *) 0) break;
  }

  return first_char;
}
