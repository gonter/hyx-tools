/*
 *  FILE %ds/dyb/dyb_0003.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-26
 *
 */

#include <memory.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_append_block (
struct DYNAMIC_BLOCK *dyb,
char *block,
long block_size)
{
  struct DYB_SEGMENT *ds;
  long fr;
  long cps;

  if (dyb == (struct DYNAMIC_BLOCK *) 0
      || block == (char *) 0) return -1;

  while (block_size > 0L)
  {
    if ((ds= dyb->DYB_last) == (struct DYB_SEGMENT *) 0
       || (fr= ds->DYBS_free) == 0L)
    {
      if ((ds= dyb_new_segment (dyb->DYB_segment_size))
           == (struct DYB_SEGMENT *) 0) return -1;

      *dyb->DYB_append= ds;
      dyb->DYB_append= &ds->DYBS_next;
      dyb->DYB_last= ds;
      if (dyb->DYB_begin == (struct DYB_SEGMENT *) 0)
        dyb->DYB_begin= ds;

      fr= ds->DYBS_free;
    }

    /* ds now points to the last dynamic block segment  */
    /* with space for fr (at least one) character...    */
    cps= (block_size > fr) ? fr : block_size;
    memcpy ((char *) ds->DYBS_append, (char *) block, (int) cps);

    block_size -= cps;
    ds->DYBS_free -= cps;
    ds->DYBS_append += cps;
    dyb->DYB_total_size += cps;
  }


  return 0;
}
