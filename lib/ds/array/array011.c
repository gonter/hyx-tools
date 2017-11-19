/*
 *  FILE %ds/array/array011.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-11-10
 *  latest update: 1996-12-11 12:40:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
int array_dispose_string (struct ARRAY_CONTROL *ac)
{
  struct ARRAY_ELEMENT *ae, *ae2;

  if (ac == (struct ARRAY_CONTROL *) 0) return -1;

  for (ae= ac->top;
       ae != (struct ARRAY_ELEMENT *) 0;
       ae= ae2)
  {
    ae2= ae->next;
    if (ae->payload != (void *) 0) free (ae->payload);
    free (ae);
  }

  free (ac);

  return 0;
}
