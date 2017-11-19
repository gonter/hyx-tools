/*
 *  FILE %ned/03/ned0342c.c
 *
 *  ned line callbacks
 *
 *  written:       1997-07-27
 *  latest update: 1999-04-25 16:30:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <stdio.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_line_test_cb (struct LINE *lp)
{
  struct LINE_CALLBACK *lcb;
  char buff [80];

  if (lp == (struct LINE *) 0
      || (lcb= lp->callbacks) == (struct LINE_CALLBACK *) 0
     ) return 0;

  sprintf (buff, "LINE %08lX has callbacks!\n", lp);
  ned_error_message (buff);

  for (;
       lcb != (struct LINE_CALLBACK *) 0;
       lcb= lcb->next)
  {
    sprintf (buff, "+ callback %08lX\n", lcb);
    ned_error_message (buff);
  }

  return -1;
}
