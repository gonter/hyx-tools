/*
 *  FILE %ned/02/ned0208.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 30: Revision
 *  latest update: 1997-09-14 11:01:00
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_upscr ()
{
  if (aw->first == (struct LINE *) 0
      || aw->first->next == (struct LINE *) 0
     ) return;

  aw->first= aw->first->next;
  wd_upscr (aw);
  if (aw->cy != aw->ay)
       aw->cy--;
  else {
         aw->WC_act= aw->WC_act->next;
         aw->znr++;
       }
}
