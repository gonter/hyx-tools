/*
 *  FILE %ned/03/ned0341a.c
 *
 *  ned line callbacks
 *
 *  written:       1997-04-12
 *  latest update: 1997-07-03 20:54:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_line_trigger_change (
struct LINE *lp,
int column,
int amount)
{
  struct LINE_CALLBACK *lcb;
  line_callback *fnc;
  int event;

  if (lp == (struct LINE *) 0) return -1;

  for (lcb= lp->callbacks;
       lcb != (struct LINE_CALLBACK *) 0;
       lcb= lcb->next)
  {
    event= lcb->event;

    if ((event & LCB_edit)
        /***** && lcb->column > column ****/
        && (fnc= lcb->func) != (line_callback *) 0
       )
      (*fnc) (LCB_edit, (void *) lp, lcb->cd,
              column, (void *) amount);
  }

  return 0;
}
