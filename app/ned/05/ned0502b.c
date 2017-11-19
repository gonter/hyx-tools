/*
 *  FILE %ned/05/ned0502b.c
 *
 *  *** THIS FUNCTION IS POSSIBLY OBSOLETE 1996-10-05 10:48:18 ***
 *
 *  delete from the cursor position to the end of the line
 *  WS: ^QY
 *  VI: D, d$
 *
 *  written:       1996-02-03: extracted from ned0502.c
 *  latest update: 1997-10-26 10:26:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_w_del2eoln (register struct WINDOWCTRL *w)
{
  struct LINE *act;
  register struct FEATURE *pftr= (struct FEATURE *) 0;
  register struct FEATURE **ppftr;
  int idx;

  if (w == (struct WINDOWCTRL *) 0
      || (act= w->WC_act) == (struct LINE *) 0
     ) return -1;

  if (act->line_flg & LINE_PROTECTED) return 0;

  idx= w->cx + w->hv - w->ax;

  if ((ppftr= ned_feature_find (act, idx, 1)) != (struct FEATURE **) 0)
  {
    pftr= *ppftr;
    if (pftr->ftr_edit_flags & (FTR_EDIT_NO_TEXT | FTR_EDIT_NO_INSERT))
      return 0;
  }

  act->lng= idx;

  txt_adj (act->lng, &act->txt);

  /* TEST: adjusting feature record */
  for (ppftr= &act->ftr;
       (pftr= *ppftr) != (struct FEATURE *) 0;
       ppftr= &pftr->ftr_next)
  {
    int ftr_pos;

    if ((ftr_pos= pftr->ftr_pos) <= idx
        && ftr_pos + pftr->ftr_replarray_size > idx /* T2D: +/- ??? */
       )
    {
      pftr->ftr_replarray_size= idx - ftr_pos;
    }

    if (ftr_pos >= idx)
    {
      ned_feature_free (pftr);

      *ppftr= (struct FEATURE *) 0;
      break;
    }
  }

  wd_displine (w, act, w->cy, w->ax, w->bx);
  w->f_upd= 1;
}
