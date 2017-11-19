/*
 *  FILE %ds/dyb/dyb_0011.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-19
 *
 */

#include <string.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
                       /*0123456789*/
static char _blanks []= "          ";

/* ------------------------------------------------------------------------ */
int dyb_append_blanks (
struct DYNAMIC_BLOCK *dyb,
long num_blanks)
{
  long s;

  if (dyb == (struct DYNAMIC_BLOCK *) 0) return -1;

  while (num_blanks > 0L)
  {
    s= (num_blanks > 10L) ? 10L : num_blanks;
    num_blanks -= s;
    dyb_append_block (dyb, _blanks, s);
  }

  return 0;
}
