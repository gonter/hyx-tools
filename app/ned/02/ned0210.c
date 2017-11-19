/*
 *  FILE %ned/02/ned0210.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-09-14 11:09:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_dnscr ()
{
  if (aw->WC_first == (struct LINE *) 0
      || aw->WC_first->prev == (struct LINE *) 0
     ) return;

  aw->WC_first= aw->WC_first->prev;
  wd_dnscr (aw);
  if (aw->cy == aw->by)
  {
    aw->WC_act= aw->WC_act->prev;
    aw->znr--;
  }
  else aw->cy++;
}
