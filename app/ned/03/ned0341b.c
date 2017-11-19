/*
 *  FILE %ned/03/ned0341b.c
 *
 *  ned line callbacks
 *
 *  written:       1997-04-12
 *  latest update: 1999-04-25 16:30:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_line_trigger_split_join (
struct LINE *lp,
struct LINE *lp2,
int column,
int action)              /* LCB_line_(split|join) */
{
  struct LINE_CALLBACK *lcb, **lcbp;
  line_callback *fnc;
  int event;
  int rc;

  if (lp == (struct LINE *) 0) return -1;
  ned_message_1 ("ned0341b callback list");

  for (lcbp= &lp->callbacks;
       (lcb= *lcbp) != (struct LINE_CALLBACK *) 0;
      )
  {
    event= lcb->event;
    rc= 0;

    if ((   ((event & LCB_line_split) && action == LCB_line_split)
         || ((event & LCB_line_join)  && action == LCB_line_join)
        )
        && (fnc= lcb->func) != (line_callback *) 0
       )
      rc= (*fnc) (action, (void *) lp, lcb->cd, column, (void *) lp2);

    if (rc == 1)
    {
      *lcbp= lcb->next;       /* lcbp must stay there */
      free (lcb);
      continue;
    }

    lcbp= &lcb->next;
  }

  return 0;
}
