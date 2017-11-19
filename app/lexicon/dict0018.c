/*
 *  FILE %lexicon/dict0018.c
 *
 *  Text Segment Liste ausgeben
 *
 *  written:       1995-08-19: reorganized from dict0008.c
 *  latest update: 1995-08-19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dyb.h>
#include <gg/parse.h>

#ifdef DIAGNOSTIC
#define hyx_unroll_text_segment_list hyx_idag_unrtxtsl
#endif /* DIAGNOSTIC */

/* ------------------------------------------------------------------------ */
int hyx_unroll_text_segment_list (
struct DYNAMIC_BLOCK *dyb,
struct TEXT_SEGMENT *ts)
{
  char *cp;
  int first_char= -1;   /* used for what??? @@@ T2D ### */

  for (;
       ts != (struct TEXT_SEGMENT *) 0;
       ts= ts->TSEG_next)
  {
    cp= ts->TSEG_text_array;
    if (first_char == -1) first_char= *cp;

#ifdef DIAGNOSTIC
    dyb_append_block (dub, "{", 1);
    dyb_append_block (dyb, cp, ts->TSEG_text_lng);
    dyb_append_block (dub, "}", 1);
#else
    dyb_append_block (dyb, cp, ts->TSEG_text_lng);
#endif /* !DIAGNOSTIC */
  }

  return first_char;
}
