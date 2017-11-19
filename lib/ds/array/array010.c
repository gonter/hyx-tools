/*
 *  FILE %ds/array/array010.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-11-10
 *  latest update: 1996-11-10  1:17:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
int array_dispose2 (struct ARRAY_CONTROL *ac, array_element_destructor *ad)
{
  struct ARRAY_ELEMENT *ae, *ae2;

  if (ac == (struct ARRAY_CONTROL *) 0) return -1;

  for (ae= ac->top;
       ae != (struct ARRAY_ELEMENT *) 0;
       ae= ae2)
  {
    ae2= ae->next;
    if (ad != (array_element_destructor *) 0) (*ad) (ae->payload);
    free (ae);
  }

  free (ac);

  return 0;
}
