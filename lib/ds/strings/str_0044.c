/*
 *  FILE %ds/strings/str_0044.c
 *
 *  free a string if not a null pointer
 *
 *  written:       1995-11-05
 *  latest update: 1995-11-05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int free_or_what (void *s)
{
  if (s != (void *) 0) free (s);

  return 0;
}
