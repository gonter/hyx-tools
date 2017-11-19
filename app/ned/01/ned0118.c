/*
 *  FILE %ned/01/ned0118.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1997-09-14 11:01:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_nl ()        /* Ctrl M */
{
  register struct WINDOWCTRL *w;
  int flg_wd_setup= 0;
  int cn;

  w= aw;
  if (w->WC_edit_mode & EDIT_READ_ONLY) return;

#ifdef USE_ABBREVIATIONS
  ned_check_abbrev ();
#endif /* USE_ABBREVIATIONS */

  /* NOTE: ev. ab hier als ned_wc_nl () auskoppeln */
  if (w->WC_act == (struct LINE *) 0) goto INS_NL;

  if (w->cy == w->by)
  {
    w->first= w->first->next;
    wd_upscr (w);
    w->cy--;
  }

INS_NL:
  if ((cn= ned_wc_ins_nl (w)) < 0) return;     /* error !! */
  w->cx= w->ax + cn;
  if (cn < w->hv)
  {
    w->hv= 0;
    w->cx= w->ax+cn;
    flg_wd_setup= 1;
  }

  if (w->WC_act->next == (struct LINE *) 0) return;     /* ### ???? */

  w->WC_act= w->WC_act->next;

  if (w->cy < w->by)
  {
    w->cy++;
  }
  else
  {
    w->first= w->first->next;
    flg_wd_setup= 1;
  }

  w->znr++;

#ifndef MSDOS
  flg_wd_setup= 1;              /* ### make sure screen is redrawn even ### */
  w->w_upd |= 0x04;             /* ### if this method is inefficient!   ### */
#endif

  if (flg_wd_setup) ned_display_window (w);
  chk_updown (w);
}
