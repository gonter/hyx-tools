/*
 *  FILE ~/usr/sgml/hytxt004.c
 *
 *  Frame Liste sortieren
 *
 *  written:       1990 02 17
 *  latest update: 1994-06-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>

#ifdef NIL
#undef NIL
#endif
#define NIL (struct HYTXT_FRAME *) 0

/* ------------------------------------------------------------------------ */
int hytxt_sort (
struct HYTXT_FRAME **liste,
int sort_mode)                  /* 0 .. unsortiert              */
                                /* 1 .. reversed                */
                                /* 2 .. Frame Namen             */
                                /* 3 .. Frame Namen reversed    */
                                /* usw..........                */
{
  struct HYTXT_FRAME
     *f1,       /* Arbeitespointer */
     *f1b,
     *f2,       /* Neue Liste */
    **f3,
    **fp;

  if (liste == (void *) 0) return -1;
  if ((f1=*liste) == NIL ||
      sort_mode < 1 || sort_mode > 4) return 0;  /* #### */

  f2= NIL;
  fp= &f2;

  /* 1. Neusortierung */
  for (; f1 != NIL; f1 = f1b)
  {
    /* Sort Modes!!!!!!!!!!!!!! #################### */
    for (f3 = &f2; *f3 != NIL; f3 = &((*f3)->hytxt_frame_next))
        if (strcmp ((*f3)->hytxt_frame_name, f1->hytxt_frame_name) > 0)
           break;

    f1b = f1->hytxt_frame_next;
    if (*f3 == NIL)
         {
           *fp = f1;
           fp = &(f1->hytxt_frame_next);
           *fp = NIL;
         }
    else {
           f1->hytxt_frame_next = *f3;
           *f3 = f1;
         }
  }

  /* 2. Rueckverkettung */
  f2->hytxt_frame_prev = NIL;
  for (f1 = f2; f1 != NIL; f1 = f1->hytxt_frame_next)
  {
    if (f1->hytxt_frame_next == NIL) break;
    f1->hytxt_frame_next->hytxt_frame_prev = f1;
  }

  *liste = f2;
  return 0;
}
