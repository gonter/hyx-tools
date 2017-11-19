/*
 *  FILE ~/usr/sgml/hytxt006.c
 *
 *  written:       1990 02 14
 *  latest update: 1994-06-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
void hytxt_hide_earlier (
struct HYTXT_FRAME **fl)        /* gescannte Frame Liste                    */
{
  struct HYTXT_FRAME *f1, *f2;

  f2= (struct HYTXT_FRAME *) 0;

  for (f1  = *fl;
       f1 != (struct HYTXT_FRAME *) 0;
       f1  = f1->hytxt_frame_next)
    if (f1->hytxt_frame_newer == (struct HYTXT_FRAME *) 0)
    {
      f1->hytxt_frame_prev = f2;
      f2 = f1;
      *fl = f1;
       fl = &(f1->hytxt_frame_next);
    }

  *fl= (struct HYTXT_FRAME *) 0;
}
