/*
 *  FILE %ds/hyxp/hyxp0020.c
 *
 *  written:       1994-11-12
 *  latest update: 1995-07-02
 *  $Id: hyxp0020.c,v 1.2 2005/09/04 09:24:39 gonter Exp $
 *
 */

#include <sys/types.h>
#include <gg/strings.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long hyx_tx_segm_count_char (struct TEXT_SEGMENT *ts, int code)
{
  long cnt= 0L;

  for (; ts != (struct TEXT_SEGMENT *) 0; ts= ts->TSEG_next)
    cnt += (long) count_char (code, ts->TSEG_text_array, ts->TSEG_text_lng);

  return cnt;
}
