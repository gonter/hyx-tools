/*
 *  FILE %ned/07/ned0747b.c
 *
 *  check if critical pointers exist in the window and realign
 *  them if necessary
 *
 *  written:       1996-05-27
 *  latest update: 1996-05-27 14:16:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int ned_blk_realign_if_critical (struct LINE *new_line)
/* 0 -> not critical    */
/* 1 -> critical        */
{
  register struct WINDOWCTRL *wc;

  for (wc= windows; wc != (struct WINDOWCTRL *) 0; wc= wc->next)
  {
    if ( (wc->WC_act != (struct LINE *) 0
          && (wc->WC_act->line_flg & LINE_inBLOCK)
         )
        ||(wc->WC_first != (struct LINE *) 0
           && (wc->WC_first->line_flg & LINE_inBLOCK)
          )
       )
    {
      wc->WC_act= new_line;
      ned_w_jmp_aktline (wc, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
    }
  }

  return 0;
}
