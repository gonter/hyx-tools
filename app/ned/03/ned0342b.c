/*
 *  FILE %ned/03/ned0342b.c
 *
 *  ned line callbacks
 *
 *  written:       1997-04-13
 *  latest update: 1999-04-25 16:30:45
 *  $Id: ned0342b.c,v 1.3 2003/10/02 06:45:51 gonter Exp $
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
int ned_line_rel_cb (
struct LINE *lp,
line_callback *fnc,
int event_mask,
void *cd)
{
  struct LINE_CALLBACK *lcb, **lcbp;

#ifdef UX_DEBUG
  printf ("0342b ned_line_rel_cb (lp=%08lX fnc=%08lX event_mask=%d cd=%08lX)\n",
  lp, fnc, event_mask, cd);
#endif

  if (lp == (struct LINE *) 0) return -1;

  for (lcbp= &lp->callbacks;
       (lcb= *lcbp) != (struct LINE_CALLBACK *) 0;
       lcbp= &lcb->next)
  {
    if (lcb->func == fnc  /* BUG HERE: see %ned/crashes */
        && lcb->cd == cd
        && lcb->event == event_mask
       )
     {
       *lcbp= lcb->next;
       free (lcb);
       break;                   /* just remove one matching handler */
     }
  }

  return 0;
}
