/*
 *  FILE %ned/05/ned0507.c
 *
 *  show the total number of lines
 *
 *  written:       1996-05-26
 *  latest update: 1998-08-16 12:31:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_show_total_lines ()
{
  int cnt;
  char buf [40];

  if (aw == (struct WINDOWCTRL *) 0) return;

  cnt= ned_cnt_total_lines (aw->WC_act);

  sprintf (buf, "%d cy=%d ay=%d", cnt, aw->cy, aw->ay);
  ned_message_1 (buf);
}
