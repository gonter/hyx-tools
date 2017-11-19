/*
 *  FILE %ned/02/ned0240.c
 *
 *  vi emulation: append after character position
 *
 *  written:       1993-07-31
 *  latest update: 1999-05-01 13:47:51
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_append ()
{
  int pos;

  if (aw != (struct WINDOWCTRL *) 0)
  {
    pos= aw->cx + aw->hv - aw->ax;
    if (aw->WC_act != (struct LINE *) 0
      && pos < aw->WC_act->lng) ned_cursor_right ();
  }
  ned_wc_ins_mode (aw, INSFLG_insert);
}
