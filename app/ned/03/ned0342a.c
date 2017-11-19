/*
 *  FILE %ned/03/ned0342a.c
 *
 *  ned line callbacks
 *
 *  written:       1997-04-13
 *  latest update: 1999-04-25 16:30:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

#ifdef UX_DEBUG
#include <stdio.h>
#endif

/* ------------------------------------------------------------------------ */
int ned_line_reg_cb (
struct LINE *lp,
line_callback *fnc,
int event_mask,
void *cd)
{
  struct LINE_CALLBACK *lcb;

#ifdef UX_DEBUG
  printf ("0342a ned_line_reg_cb (lp=%08lX fnc=%08lX event_mask=%d cd=%08lX)\n",
  lp, fnc, event_mask, cd);
#endif

  if (lp == (struct LINE *) 0
      || (lcb= calloc (sizeof (struct LINE_CALLBACK), 1))
           == (struct LINE_CALLBACK *) 0
     ) return -1;

  lcb->func= fnc;
  lcb->cd= cd;
  lcb->event= event_mask;

  lcb->next= lp->callbacks;
  lp->callbacks= lcb;

  return 0;
}
