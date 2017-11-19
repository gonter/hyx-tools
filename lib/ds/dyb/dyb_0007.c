/*
 *  FILE ~/usr/ds/dyb/dyb_0007.c
 *
 *  manipulation of dynamic blocks:
 *  *** TEST @@@ TEST ###
 *  truncate a dynamic block at a certain position
 *  *** TEST @@@ TEST ###
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-20
 *
 */

#include <stdlib.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
long dyb_truncate (struct DYNAMIC_BLOCK *dyb, long size)
{
  struct DYB_SEGMENT *ds;
  struct DYB_SEGMENT *ds2;
  long s;
  int cut_off= 0;

  if (dyb == (struct DYNAMIC_BLOCK *) 0) return -1L;

  for (ds= dyb->DYB_begin;
       ds != (struct DYB_SEGMENT *) 0;
       ds= ds2)
  {
    ds2= ds->DYBS_next;

    if (cut_off)
    {
      free (ds);
      continue;
    }

    s= ds->DYBS_size - ds->DYBS_free;

    if (size - s >= 0L) goto NEXT;

    cut_off= 1;
    ds->DYBS_append= ds->DYBS_block + size;
    ds->DYBS_free= ds->DYBS_size - size;

NEXT:
    size -= s;
    dyb->DYB_total_size -= s;
  }

  return (size > 0L) ? size : 0L;
}
