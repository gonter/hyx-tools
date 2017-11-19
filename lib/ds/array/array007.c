/*
 *  FILE %ds/array/array007.c
 *
 *  processing of arrays (similar to perl)
 *
 *  written:       1996-11-10
 *  latest update: 1996-11-10  0:55:30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/array.h>

/* ------------------------------------------------------------------------ */
long array_push2 (struct ARRAY_CONTROL **ac, void *pl)
{
  if (ac == (struct ARRAY_CONTROL **) 0
      || (*ac == (struct ARRAY_CONTROL *) 0
          && (*ac= array_new ()) == (struct ARRAY_CONTROL *) 0
         )
     ) return -1L;

  return array_push (*ac, pl);
}
