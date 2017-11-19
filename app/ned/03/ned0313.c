/*
 *  FILE %ned/03/ned0313.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *                 1991 06 02: Revision
 *  latest update: 1997-10-26 10:27:04
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
void p_turn_line ()     /* Zwei Zeilen vertauschen */
{
  struct LINE *ltmp;
  struct LINE *aw_act;
  int new_first= 0;

  if ((aw_act= aw->WC_act) == (struct LINE *) 0
      || (ltmp= aw_act->WC_next) == (struct LINE *) 0
     ) return;

  if (aw_act->WC_prev == (struct LINE *) 0) new_first= 1;

  /* handle block flags ... nasty, long work :(( */
  if (aw_act == b_beg.ptr)
  {
    if (ltmp == b_end.ptr)
    { /* switch block begin and block end!!! */
      struct LINE *p;
      int o;

      p=            b_beg.ptr;
      o=            b_beg.offset;
      b_beg.ptr=    b_end.ptr;
      b_beg.offset= b_end.offset;
      b_end.ptr=    p;
      b_end.offset= o;
    }
    else
    if (!(aw_act == b_end.ptr))
      ltmp->line_flg &= LINE_BLOCK_CLR;
  }
  else
  if (ltmp == b_beg.ptr)
  {
    if (!(ltmp == b_end.ptr))
      aw_act->line_flg |= LINE_BLOCK_INBLOCK;
  }
  else
  if (aw_act == b_end.ptr)
  {
    ltmp->line_flg |= LINE_BLOCK_INBLOCK;
  }
  else
  if (ltmp == b_end.ptr)
  {
    aw_act->line_flg &= LINE_BLOCK_CLR;
  }

  ltmp->prev= aw_act->prev;
  aw_act->prev= ltmp;
  if (ltmp->next != (struct LINE *) 0) ltmp->next->prev= aw_act;
  if (!new_first) ltmp->prev->next= ltmp;
  aw_act->next= ltmp->next;
  ltmp->next= aw_act;
  aw->WC_act= ltmp;
  if (new_first) aw->first= ltmp;

  aw->f_upd= 1;
  ned_display_window (aw);
}
