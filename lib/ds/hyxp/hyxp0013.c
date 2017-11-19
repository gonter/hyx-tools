/*
 *  FILE ~/usr/ds/hyxp/hyxp0013.c
 *
 *  written:       1991 03 18
 *  latest update: 1995-03-30: moved to %ds/hyxp
 *
 */

#include <stdlib.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long _hyx_txsegm_freed= 0L;
long _hyx_txsegm_free_size= 0L;

/* ------------------------------------------------------------------------ */
int hyx_frtx_segm_list (struct TEXT_SEGMENT *ts1)
{
  struct TEXT_SEGMENT *ts2;

  while (ts1 != (struct TEXT_SEGMENT *) 0)
  {
    ts2= ts1->TSEG_next;

    _hyx_txsegm_free_size += ts1->TSEG_text_lng
                               + 1L
                               + (long) sizeof (struct TEXT_SEGMENT);
    _hyx_txsegm_freed++;

    free (ts1);
    ts1= ts2;
  }

  return 0;
}
