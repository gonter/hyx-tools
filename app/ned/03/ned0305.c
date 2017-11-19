/*
 *  FILE %ned/03/ned0305.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1997-01-19  0:28:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_wc_insert (
register struct WINDOWCTRL *w,
int  k,                 /* character to insert                              */
int  df)                /* display flag: 1 -> display line after inserting  */
{
  if (w->WC_act == (struct LINE *) 0)
  {
    ned_wc_ins_nl (w);
    if (w->WC_act == (struct LINE *) 0) return;
       /* Error: zu wenig Speicher ?               */
  }

  qq_insert (w->WC_act, w->hv + w->cx - w->ax, k, w->ins_flg);

  w->f_upd= 1;

  if (df) wd_displine (w, w->WC_act, w->cy, w->ax, w->bx);
}
