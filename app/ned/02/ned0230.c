/*
 *  FILE %ned/02/ned0230.c
 *
 *  Window Control Struktur aufbauen
 *
 *  written:       1991 05 29
 *  latest update: 2001-02-11 21:58:10
 *  $Id: ned0230.c,v 1.3 2001/02/12 00:03:25 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int q_wdwopen (struct WINDOWCTRL **wc, int *win_num)
{
  struct WINDOWCTRL *last_window;

  *win_num= 1;

  if ((*wc= ned_create_window_pair ()) == (struct WINDOWCTRL *) 0) return -1;

  (*wc)->next= (struct WINDOWCTRL *) 0;
  (*wc)->file_type= FTY_PLAIN;

  if (windows == (struct WINDOWCTRL *) 0)
  { /* Spezialfall: noch ueberhaupt kein Window erzeugt! */
    windows= *wc;
    (*wc)->prev= (struct WINDOWCTRL *) 0;
  }
  else
  {
    for (last_window= windows;
         last_window->next != (struct WINDOWCTRL *) 0;
         last_window= last_window->next) (*win_num)++;

    (*wc)->prev= last_window;
    last_window->next= *wc;
    (*win_num)++;
  }

#ifdef USE_TK
  ned_tk_associate_window (*wc);
#endif

  return 0;
}
