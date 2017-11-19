/*
 *  FILE %ds/dyb/dyb_0004.c
 *
 *  manipulation of dynamic blocks
 *
 *  written:       1995-08-19
 *  latest update: 1995-08-26
 *
 */

#include <string.h>
#include <gg/dyb.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int dyb_append_string (
struct DYNAMIC_BLOCK *dyb,
char *string)
{
  if (dyb == (struct DYNAMIC_BLOCK *) 0
      || string == (char *) 0) return -1;

  return dyb_append_block (dyb, string, (long) strlen (string));
}
