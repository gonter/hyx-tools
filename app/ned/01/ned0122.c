/*
 *  FILE %ned/01/ned0122.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen  usw.
 *
 *  written:       1987 04 08
 *                 1991 01 31: Revision
 *  latest update: 1997-09-07 13:15:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int repeat;

/* ------------------------------------------------------------------------ */
void ned_del_char_right ()
{
  if (aw->WC_act == (struct LINE *) 0
      || (aw->WC_edit_mode & EDIT_READ_ONLY)
     ) return;

  if (aw->cx + aw->hv - aw->ax == aw->WC_act->lng)
  {
    if (aw->WC_act->next == (struct LINE *) 0) return;
    if (aw->WC_act->txt == (struct TXT *) 0)
    {
      if (ned_delete_current_line (aw) <= 0) return;
    }
    else ned_join3 (aw);

    ned_display_window (aw);
  }
  else ned_wc_delete (aw, 1);
}
