/*
 *  FILE %ds/hyxp/hyxp0009.c
 *
 *  Erzeugung von Text Segmenten
 *
 *  written:       1991 03 12
 *                 1991 03 27
 *                 1995-03-30: moved to %ds/hyxp
 *  latest update: 1995-07-02
 *  $Id: hyxp0009.c,v 1.3 2004/05/08 15:40:21 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long _hyx_text_segment_allocated= 0L;
long _hyx_text_segment_alloc_size= 0L;

/* ------------------------------------------------------------------------ */
struct TEXT_SEGMENT *hyx_mktx_segm (char *s, long lng)
{
  struct TEXT_SEGMENT *seg;
  int siz;

  if (lng == 0L || s == (char *) 0) return (struct TEXT_SEGMENT *) 0;

  siz= sizeof (struct TEXT_SEGMENT) + (int) lng;

  if ((seg= (struct TEXT_SEGMENT *) calloc (siz+1, 1))
      == (struct TEXT_SEGMENT *) 0) return (struct TEXT_SEGMENT *) 0;

  _hyx_text_segment_allocated++;
  _hyx_text_segment_alloc_size += (long) (siz+1);

  seg->sig= SIG_TEXT_SEGMENT;

  seg->TSEG_next= (struct TEXT_SEGMENT *) 0;
  seg->TSEG_text_lng= lng;

  memcpy (seg->TSEG_text_array, s, (int) lng);
  seg->TSEG_text_array [lng]= 0;

  return seg;
}
