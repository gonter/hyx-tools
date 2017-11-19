/*
 *  FILE %ds/array/array003.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-08-11
 *  latest update: 1997-03-30  9:25:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
long array_push (struct ARRAY_CONTROL *ac, void *pl)
{
  struct ARRAY_ELEMENT *ae;
  struct ARRAY_ELEMENT *ae_last;

  if (ac == (struct ARRAY_CONTROL *) 0
      || (ae= array_new_element ()) == (struct ARRAY_ELEMENT *) 0
     ) return -1L;

  ae->payload= pl;

  if (ac->elements > 0L)
  { /* there were already a few elements */
    ae_last= ac->last;
    ae_last->next= ae;
    ae->prev= ae_last;
    ac->last= ae;
    ac->elements++;
  }
  else
  {
    ac->elements= 1L;
    ac->top= ac->last= ae;
  }

  return ac->elements;
}
