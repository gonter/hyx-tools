/*
 *  FILE %ds/array/array014.c
 *
 *  create a temporary duplicate of an array
 *  but without duplicating the payload!!
 *
 *  T2D: this could be implemented faster by avoiding the array_push ()
 *
 *  written:       1997-11-09
 *  latest update: 1997-11-09 12:15:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
struct ARRAY_CONTROL *array_dup_tmp (struct ARRAY_CONTROL *ac)
{
  struct ARRAY_CONTROL *dup= (struct ARRAY_CONTROL *) 0;
  struct ARRAY_ELEMENT *ae;

  if (ac == (struct ARRAY_CONTROL *) 0
      || (dup= array_new ()) == (struct ARRAY_CONTROL *) 0
     ) goto DONE;

  for (ae= ac->top;
       ae != (struct ARRAY_ELEMENT *) 0;
       ae= ae->next)
  {
    array_push (dup, ae->payload);
  }

DONE:
  return dup;
}
