/*
 *  FILE %ned/05/ned0502d.c
 *
 *  delete from the cursor position to the begin of the line
 *  WS: ??
 *  VI: d^, d0
 *
 *  written:       1996-10-05
 *  latest update: 1997-08-28 11:41:44
 *  $Id: ned0502d.c,v 1.2 2001/09/28 18:48:28 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_w_del2boln (register struct WINDOWCTRL *w, int opcode)
{
  struct LINE *act_beg;
  struct LINE *act_rest;
  struct LINE *lp;
  register struct FEATURE *pftr= (struct FEATURE *) 0;
  register struct FEATURE **ppftr;
  int idx;
  int flg_redraw= 0;            /* 1 -> redraw the complete window */
  int flg_act_is_first= 0;

  if (w == (struct WINDOWCTRL *) 0
      || (act_beg= w->WC_act) == (struct LINE *) 0
     ) return -1;

  if (act_beg->line_flg & LINE_PROTECTED) return 0;

  if (act_beg == w->WC_first) flg_act_is_first= 1;
  idx= w->cx + w->hv - w->ax;

  if ((ppftr= ned_feature_find (act_beg, idx, 1)) != (struct FEATURE **) 0)
  {
    pftr= *ppftr;
    if (pftr->ftr_edit_flags & (FTR_EDIT_NO_TEXT | FTR_EDIT_NO_INSERT))
      return 0;
  }

  if (ned_split (act_beg, &act_rest, idx, 0) < 0) return -1;

  /******************** BEGIN ***************************/
  /* possible operations here:                          */
  /* 1. delete first part                            OK */
  /* 2. delete second part                           OK */
  /* 3. flip both parts           (Not Yet Implemented) */

  switch (opcode)
  {
    case 1:
      /* let the two parts switch places */
      act_rest->next= act_beg->next;
      act_rest->prev= act_beg->prev;
      if ((lp= act_rest->prev) != (struct LINE *) 0) lp->next= act_rest;
      if ((lp= act_rest->next) != (struct LINE *) 0) lp->prev= act_rest;

      w->WC_act= act_rest;
      w->cx= w->ax;
      if (w->hv)
      {
        w->hv= 0;
        flg_redraw= 1;
      }

      if (flg_act_is_first) w->WC_first= w->WC_act;
      /* drop the old line begin */
      act_beg->next= act_beg->prev= (struct LINE *) 0;

      ned_line_trigger_delete (act_beg, 1, 1);
      ned_store_line_to_buffer (-1, act_beg, act_beg, 0);
      break;

    case 2:
      ned_line_trigger_delete (act_rest, 1, 1);
      ned_store_line_to_buffer (-1, act_rest, act_rest, 0);
      break;
  }
  /******************** END ***************************/

  /* display the result */
  if (flg_redraw)
    ned_display_window (w);
  else
    wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);

  w->f_upd= 1;

  return 0;
}
