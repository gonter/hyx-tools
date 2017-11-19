/*
 *  FILE %ds/array/array006.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-08-11
 *  latest update: 1996-08-11 12:10:34
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
void *array_shift (struct ARRAY_CONTROL *ac)
{
  struct ARRAY_ELEMENT *ae_top;
  struct ARRAY_ELEMENT *ae_next;
  void *pl;

  if (ac == (struct ARRAY_CONTROL *) 0
      || ac->elements <= 0L
      || (ae_top= ac->top) == (struct ARRAY_ELEMENT *) 0
     ) return (void *) 0;

  pl= ae_top->payload;

  if (ac->elements == 1L)
  {
    ac->top= ac->last= (struct ARRAY_ELEMENT *) 0;
  }
  else
  {
    ae_next= ae_top->next;
    ac->top= ae_next;
    ae_next->prev= (struct ARRAY_ELEMENT *) 0;
  }

  ac->elements--;
  free (ae_top);

  return pl;
}
