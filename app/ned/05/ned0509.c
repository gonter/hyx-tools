/*
 *  FILE %ned/05/ned0509.c
 *
 *  insert a new line at the current cursor position,
 *  that is: divide two lines
 *
 *  written:       1987 04 08
 *                 1991 01 27: Split Funktion extrahiert
 *                 1991 06 25: Revision
 *  latest update: 1999-04-25 16:31:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_wc_ins_nl (struct WINDOWCTRL *wc)
{
  int rc= 0;
  struct LINE *nl;

  if (wc->file_type == FTY_FTRWDW) return -1;

  wc->f_upd= 1;
  if (wc->WC_act == (struct LINE *) 0)
  {
    wc->first= wc->WC_act= nl= alloc_line ();
    wc->tlines= 1;
#ifdef MSDOS
    if (wc->bin_eoln == 0x0A) nl->line_flg |= LINE_CODE_0x0D;
    /* ANM: Leeres Window. Annahme, dass hier MSDOS Lines erzeugt  */
    /*      werden soll, mit 0x0D 0x0A                             */
#endif
  }
  else
  {
    if ((rc= ned_split2 (wc->WC_act, &nl, wc->cx + wc->hv - wc->ax, wc->ai))
        >= 0) wc->tlines++;
  }

  /* Screen Update */
  if (wc->cy+1 < wc->by)
    w_scrblk_down (wc->ax, wc->cy+1, wc->bx, wc->by, wc->attr_text, 1);

  if (wc->cy < wc->by)
    wd_displine (wc, wc->WC_act->next, wc->cy+1, wc->ax, wc->bx);
  wd_displine (wc, wc->WC_act, wc->cy, wc->ax, wc->bx);

  setcup (wc);
  if (rc >= 0) ned_show_display_range (wc);

  return rc;
}
