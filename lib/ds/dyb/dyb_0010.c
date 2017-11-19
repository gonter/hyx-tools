/*
 *  FILE %ds/dyb/dyb_0010.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-26
 *
 */

#include <unistd.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_write (int fd, struct DYNAMIC_BLOCK *dyb)
{
  struct DYB_SEGMENT *ds;
  int s;

  if (fd < 0) return 0;
  if (dyb == (struct DYNAMIC_BLOCK *) 0) return -1;

  for (ds= dyb->DYB_begin;
       ds != (struct DYB_SEGMENT *) 0;
       ds= ds->DYBS_next)
  {
    s= (int) (ds->DYBS_size - ds->DYBS_free);

    if (write (fd, ds->DYBS_block, s) != s) return -1;
  }

  return 0;
}
