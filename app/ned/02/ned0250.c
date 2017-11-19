/*
 *  FILE %ned/02/ned0250.c
 *
 *  vi emulation: change text block
 *
 *  written:       1996-02-03
 *  latest update: 1999-05-01 13:47:12
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int vi_change_text (struct WINDOWCTRL *w, int mode, int count)
{
  int t1, idx;
  struct LINE *lp;

  if (w == (struct WINDOWCTRL *) 0
      || (lp= w->WC_act) == (struct LINE *) 0
      || count < 0
     ) return -1;

  switch (mode)
  {
    case VI_CHG_WORD: /* change word */
      t1= get_txt (lp, idx= w->hv + w->cx - w->ax);
      if (t1 == -1) return -1;
      if (t1 == ' ' || t1 == '\t')
      {
        ned_wc_delete (w, 1);
      }
      else
      {
        ned_lp_delete_word (lp, idx, 0);
DISP_LINE:
        w->f_upd= 1;
        wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);
      }
      break;

    case VI_CHG_WORD3: /* change big word */
      t1= get_txt (lp, idx= w->hv + w->cx - w->ax);
      if (t1 == -1) return -1;
      ned_lp_delete_word (lp, idx, 3);
      goto DISP_LINE;

    case VI_CHG_WORD4: /* change big word */
      t1= get_txt (lp, idx= w->hv + w->cx - w->ax);
      if (t1 == -1) return -1;
      ned_lp_delete_word (lp, idx, 4);
      goto DISP_LINE;

    case VI_CHG_2BOLN: /* change text until end of line */
      ned_w_del2boln (w, 1);
      break;

    case VI_CHG_LINE: /* change complete line */
      ned_w_jmp_in_line (w, NEDJMP_BOLN, 0);

    case VI_CHG_2EOLN: /* change text until end of line */
      ned_w_del2boln (w, 2);
      break;

    case VI_CHG_CHAR: /* substitute character */
      ned_wc_delete (w, count);
#ifdef __OLD__ /* 1997-08-03  9:30:33 */
      qq_delete (w->WC_act, w->hv + w->cx - w->ax, count);
      wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);
      w->f_upd= 1;
#endif
      break;
  }

  ned_wc_ins_mode (w, INSFLG_insert);

  return 0;
}
