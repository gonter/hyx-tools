/*
 *  FILE %ds/array/array002.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-08-11
 *  latest update: 1997-11-09 12:15:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
int array_dispose (struct ARRAY_CONTROL *ac)
{
  struct ARRAY_ELEMENT *ae, *ae2;
  array_element_destructor *ad;

  if (ac == (struct ARRAY_CONTROL *) 0) return -1;
  ad= ac->element_destructor;

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
