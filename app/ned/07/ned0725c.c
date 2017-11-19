/*
 *  FILE %ned/07/ned0726c.c
 *
 *  insert a block into a line, taking block mode into consideration
 *
 *  written:       1996-05-27
 *  latest update: 1997-08-28 11:11:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern int blk;

#define JUMP

/* ------------------------------------------------------------------------ */
int ned_blk_insert3 (           /* Block einfaedeln                         */
struct WINDOWCTRL *wc,          /* window where everything happens          */
struct LINE *la,                /* Begin des einzufuegenden Blocks          */
struct LINE *lb,                /* Ende des einzufuegenden Blocks           */
int before)                     /* 0: insert after current line             */
                                /* 1: in line mode, insert before act. line */
{
  int zn;
  struct LINE *a;

  if (wc->WC_act == (struct LINE *) 0)
  {
    wc->WC_act= wc->WC_first= la;
  }
  else
  {
    if (before && block_mode == BLOCK_MODE_line)
    {
      if ((a= wc->WC_act->prev) == (struct LINE *) 0)
      {
        if (lb != (struct LINE *) 0)
        {
          lb->next= wc->WC_act;
          wc->WC_act->prev= lb;
        }
      }
      else
      {
        ned_blk_insert (a, la, lb);
        ned_set_block_markers (wc, la, 0, 0, 0);
        ned_set_block_markers (wc, lb, 0, 1, 0);
      }
    }
    else
    {
      int offset;
      struct MARKER *mrk;
      struct LINE *lp;

      ned_blk_insert2 (wc->WC_act, offset= wc->cx + wc->hv - wc->ax, la, lb);
      lp= wc->WC_act;
      if (block_mode == BLOCK_MODE_line) lp= lp->next;
      ned_set_block_markers (wc, lp, offset, 0, 0);

      if ((mrk= ned_get_marker (NED_TMARK_INSERT2, 0)) != (struct MARKER *) 0)
      {
        ned_set_block_markers (wc, mrk->ptr, mrk->offset, 1, 0);
        mrk->wptr= wc;  /* this was not set before */
      }
    }
  }

  wc->f_upd= 1;
  wc->znr= zn= ned_cnt_line_2beg (a= wc->WC_act);
  wc->tlines= ((zn > 1) ? zn-1 : 0) + ned_cnt_line_2end (a);

#ifdef JUMP
  ned_w_jmp_aktline (wc, NEDJMP_LINE_3, 0,
                     NEDJMP_FLAG_REDRAW|NEDJMP_FLAG_NO_CNT);
#else
  wc->w_upd |= 0x04;
  ned_display_window (wc);
#endif

  return 0;
}
