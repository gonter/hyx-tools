/*
 *  FILE %ds/dyb/dyb_0001.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-26
 *
 */

#include <stdlib.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
struct DYB_SEGMENT *dyb_new_segment (int segment_size)
{
  struct DYB_SEGMENT *ds;

  if (segment_size <= 0) segment_size= DYB_SEGMENT_SIZE;

  if ((ds= (struct DYB_SEGMENT *)
            calloc (sizeof (struct DYB_SEGMENT) + segment_size, 1))
      != (struct DYB_SEGMENT *) 0)
  {
    ds->DYBS_size= ds->DYBS_free= segment_size;
    ds->DYBS_append= ds->DYBS_block;
  }

  return ds;
}
