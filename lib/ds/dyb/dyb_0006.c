/*
 *  FILE ~/usr/ds/dyb/dyb_0006.c
 *
 *  manipulation of dynamic blocks:
 *  increment reference counter for a block
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-19
 *
 */

#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_reference (struct DYNAMIC_BLOCK *dyb)
{
  if (dyb == (struct DYNAMIC_BLOCK *) 0) return -1;

  dyb->DYB_reference_counter++;

  return 0;
}
