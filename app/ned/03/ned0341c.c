/*
 *  FILE %ned/03/ned0341c.c
 *
 *  ned line callbacks
 *
 *  written:       1997-04-29
 *  latest update: 1999-04-25 16:30:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* #define DEBUG */
#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_line_trigger_delete (struct LINE *lp, int destroy, int cycle)
{
  struct LINE_CALLBACK *lcb, **lcbp;
  line_callback *fnc;
  int event;

  while (lp != (struct LINE *) 0)
  {

#ifdef DEBUG
fprintf (stderr, "0341c: lcb trigger delete lp=%08lX\n", lp);
#endif /* DEBUG */

    for (lcbp= &lp->callbacks;
         (lcb= *lcbp) != (struct LINE_CALLBACK *) 0;)
    {
      event= lcb->event;

      if ((event & LCB_delete)
          /***** && lcb->column > column ****/
          && (fnc= lcb->func) != (line_callback *) 0
         )
      {
        (*fnc) (LCB_delete, (void *) lp, lcb->cd, 0, (void *) 0);
        /* e.g. ned_marker_callback */
      }

      if (destroy)
      {
        *lcbp= lcb->next;
        free (lcb);
      }
      else
      {
        lcbp= &lcb->next;
      }
    }

    if (!cycle) break;
    lp= lp->next;
  }

  return 0;
}
