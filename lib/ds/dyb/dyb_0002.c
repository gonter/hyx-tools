/*
 *  FILE %ds/dyb/dyb_0002.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-12-16
 *
 */

#include <stdlib.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
struct DYNAMIC_BLOCK *dyb_new_block (int segment_size)
{
  struct DYNAMIC_BLOCK *dyb;

  if (segment_size <= 0) segment_size= 256;

  if ((dyb= (struct DYNAMIC_BLOCK *)
            calloc (sizeof (struct DYNAMIC_BLOCK), 1))
      != (struct DYNAMIC_BLOCK *) 0)
  {
    dyb->DYB_reference_counter= 1L;
    dyb->DYB_segment_size= segment_size;
    dyb->DYB_append= &dyb->DYB_begin;
  }

  return dyb;
}
