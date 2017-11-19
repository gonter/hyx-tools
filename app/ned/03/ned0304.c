/*
 *  FILE %ned/03/ned0304.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1997-01-19  0:36:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void q_insert (
int  k,                 /* character to insert                              */
int  df)                /* display flag: 1 -> display line after inserting  */
{
  register struct WINDOWCTRL *w;
  int curx;
  int insflg;

  w= aw;
  curx= w->cx - w->ax + w->hv;
  insflg= w->ins_flg;

  if (w->WC_edit_mode & EDIT_READ_ONLY) return;
  if (w->wwc
      && curx > w->wwc
      && (k == 0x20 || k == 0x09))
  {
    p_nl ();
    return;
  }

  if (k == 0x0100)      /* toggle character value at cursor position */
  {
    int ch;

    ch= get_txt (w->WC_act, curx);
    if (ch < 0 || ch > 0xFF) return;
    if (ch >= 'A' && ch <= 'Z') ch= ch - 'A' + 'a'; else
    if (ch >= 'a' && ch <= 'z') ch= ch - 'a' + 'A';
    k= ch;
    w->ins_flg= INSFLG_overwrite;
  }

  ned_wc_insert (w, k, df);
  w->ins_flg= insflg;
  ned_q_cursor_right (w, df);
}
