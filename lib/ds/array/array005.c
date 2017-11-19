/*
 *  FILE %ds/array/array005.c
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
void *array_pop (struct ARRAY_CONTROL *ac)
{
  struct ARRAY_ELEMENT *ae_last;
  struct ARRAY_ELEMENT *ae_prev;
  void *pl;

  if (ac == (struct ARRAY_CONTROL *) 0
      || ac->elements <= 0L                     /* 0 is ok, ERROR if less!  */
      || (ae_last= ac->last) == (struct ARRAY_ELEMENT *) 0 /* ERROR!!!      */
     ) return (void *) 0;

  pl= ae_last->payload;

  if (ac->elements == 1L)
  {
    ac->top= ac->last= (struct ARRAY_ELEMENT *) 0;
  }
  else
  {
    ae_prev= ae_last->prev;
    ac->last= ae_prev;
    ae_prev->next= (struct ARRAY_ELEMENT *) 0;
  }

  ac->elements--;
  free (ae_last);

  return pl;
}
