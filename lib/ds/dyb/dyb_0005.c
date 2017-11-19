/*
 *  FILE %ds/dyb/dyb_0005.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1997-06-16 18:34:02
 *
 */

#include <stdlib.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_destroy_block (struct DYNAMIC_BLOCK *dyb)
{
  struct DYB_SEGMENT *ds;
  struct DYB_SEGMENT *ds2;

  if (dyb == (struct DYNAMIC_BLOCK *) 0
      || --dyb->DYB_reference_counter > 0) return 0;

  for (ds= dyb->DYB_begin;
       ds != (struct DYB_SEGMENT *) 0;
       ds= ds2)
  {
    ds2= ds->DYBS_next;
    free (ds);
  }

  free (dyb);
  
  return 0;
}
