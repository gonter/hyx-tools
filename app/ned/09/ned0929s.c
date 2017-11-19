/*
 *  FILE %ned/09/ned0929s.c
 *
 *  written:       1996-07-22
 *  latest update: 1996-10-29 16:32:34
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tk.h>
#include <tcl.h>

#include <stdio.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
int ned_tk_show_display_range (struct WINDOWCTRL *w)
{
  int xlines;           /* Zahl der Zeilen im File                          */
  int first_line;       /* Nummer der 1. Zeile am Schirm                    */
  int last_line;
  double top, bottom;
  char cmd_line [80];
  NED_Widget *nw;

  if (w == (struct WINDOWCTRL *) 0
      || (nw= w->wc_widget) == (NED_Widget *) 0
     ) return -1;

  xlines= w->tlines;
  first_line= w->znr - w->cy;
  if (xlines <= 0 || first_line > xlines)
  { /* xlines unplausibel; fehlerhafte Berechnung??? */
    xlines= w->tlines= ned_cnt_total_lines (w->WC_act);
  }

  last_line= first_line + w->by;
  first_line += w->ay - 1;

  top= ((double) first_line) / ((double) xlines);
  bottom= ((double) last_line) / ((double) xlines);

  sprintf (cmd_line, "%s.sb set %g %g", nw->window_path, top, bottom);
#ifdef DIAG
fprintf (stderr,
         "ned0929s: first_line=%d xlines=%d last_line=%d\n",
         first_line, xlines, last_line);
fprintf (stderr,
         "ned0929s: cmd_line='%s'\n",
         cmd_line);
#endif

  Tcl_Eval (nw->interp, cmd_line);

  return 0;
}
