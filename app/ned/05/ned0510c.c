/*
 *  FILE %ned/05/ned0510b.c
 *
 *  delete the current line in a window, no display
 *  see also: %ned/05/ned0510.c
 *
 *  written:       1987 04 08: as del_line
 *                 1991 02 07: Revision
 *                 1991 05 26: Revision
 *                 1994-12-27: extracted from ned0510.c
 *  latest update: 1998-08-16 19:38:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_delete_a_line (
register struct WINDOWCTRL *w,          /* current window                   */
register struct LINE *lp)               /* pointer to current line          */
                                        /* which will be deleted            */
/* return value:                                                            */
/* -1: didn't do anything                                                   */
/* 0: nothing has been changed                                              */
/* bit 0: line was last on screen                                           */
/* bit 1: line was first on screen                                          */
/* bit 2: something has been edited                                         */
{
  register struct LINE *lp_next;        /* pointer to next line             */
  register struct LINE *lp_prev;        /* pointer to previous line         */
  int rc= 0;

  if (w == (struct WINDOWCTRL *) 0
      || (w->WC_edit_mode & EDIT_READ_ONLY)
      || w->file_type == FTY_FTRWDW
      || lp == (struct LINE *) 0
     ) return -1;

  if (lp->line_flg & LINE_PROTECTED) return 0;

  w->f_upd= 1;
  w->tlines--;
  rc= 4;

  if ((lp_next= lp->next) == (struct LINE *) 0)
  { /* last line on the screen */
    if (lp->prev == (struct LINE *) 0)
    { /* last line on screen is also the first one, delete everything */
      w->WC_act= w->first= (struct LINE *) 0;
      w->znr= 0;
      w->tlines= 0;
      w->cy= w->ay;
      w->cx= w->ax;

      rc= 3;
    }
    else
    { /* this is the last line but there are others before */

      lp_prev= lp->prev;
      lp_prev->next= (struct LINE *) 0;
      w->WC_act= lp_prev;       /* at last line, set current line to prev   */
      if (w->first == lp) w->first= w->WC_act;

      ned_line_trigger_delete (lp, 1, 0);

      if (w->cy != w->ay) w->cy--;
      else if (w->first->prev != (struct LINE *) 0)
             w->first= w->first->prev;

      w->znr--;
      rc= 1;
    }
  }
  else
  { /* this is any line on the screen, but could also be the first          */
    /* thus lp_next is not (struct LINE *) 0                                */
    lp_next->prev= lp->prev;
    w->WC_act= lp_next;
    if (lp->prev == (struct LINE *) 0)
         rc= 2;
    else lp->prev->next= lp_next;

    ned_line_trigger_delete (lp, 1, 0);

    if (w->first == lp) w->first= w->WC_act;
  }

  lp->next= lp->prev= (struct LINE *) 0;
  ned_store_line_to_buffer (-1, lp, lp, 1);

  return rc;
}
