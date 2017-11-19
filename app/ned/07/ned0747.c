/*
 *  FILE %ned/07/ned0747.c
 *
 *  check if block has critical pointers like w->first or w->WC_act
 *  pointing into the block
 *
 *  written:       1991-12-31
 *  latest update: 1996-07-26  3:09:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int ned_blk_critical ()
/* 0 -> not critical    */
/* 1 -> critical        */
{
  register struct WINDOWCTRL *w;

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->next)
  {
    if ( (w->WC_act   != (struct LINE *) 0 && (w->WC_act  ->line_flg & LINE_inBLOCK))
       ||(w->WC_first != (struct LINE *) 0 && (w->WC_first->line_flg & LINE_inBLOCK)) )
      return 1;
  }

  return 0;
}
