/*
 *  FILE %ned/03/ned0330.c
 *
 *  delete word modes:
 *  0 .. vi de
 *  1 .. like vi de but join lines if EOLN
 *  2 .. vi dw
 *  3 .. vi dW
 *  4 .. vi dE
 *
 *  written:       1991 01 31
 *  latest update: 1999-05-01  9:58:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int COL_TEXT;

/* ------------------------------------------------------------------------ */
void ned_delete_word (void)  /* former p_delete_word */
{
  set_repeat_command (ned_delete_word);
  ned_wc_delete_word (aw, 0);
}

/* ------------------------------------------------------------------------ */
void ned_delete_word_2 (void)
{
  set_repeat_command (ned_delete_word_2);
  ned_wc_delete_word (aw, 2);
}

/* ------------------------------------------------------------------------ */
void ned_delete_word_3 (void)
{
  set_repeat_command (ned_delete_word_3);
  ned_wc_delete_word (aw, 3);
}

/* ------------------------------------------------------------------------ */
void ned_delete_word_4 (void)
{
  set_repeat_command (ned_delete_word_4);
  ned_wc_delete_word (aw, 4);
}

/* ------------------------------------------------------------------------ */
int ned_wc_delete_word (struct WINDOWCTRL *wc, int mode)
{
  int delete_idx;

  if (wc->WC_act == (struct LINE *) 0
      || (wc->WC_edit_mode & EDIT_READ_ONLY)
     ) return -1;

  delete_idx= wc->cx + wc->hv - wc->ax;

  if (mode == 1) /* this is not used anywhere */
  {
    /* Dieser Abschnitt dient dazu am Ende einer Zeile die Zeile  */
    /* mit der naechsten Zeile zusammenzufuegen. (wie CTRL-G)     */
    if (delete_idx == wc->WC_act->lng)
    {
      if (wc->WC_act->txt == (struct TXT *) 0)
           ned_wc_delete_line (wc, 1, COL_TEXT);
      else ned_join3 (wc);
      ned_display_window (wc);
      return 0;
    }
    mode= 0;    /* else: perform normal delete operation im mode 0 */
  }

  ned_lp_delete_word (wc->WC_act, delete_idx, mode);
  wc->f_upd= 1;
  wd_displine (wc, wc->WC_act, wc->cy, wc->ax, wc->bx);

  return 0;
}
