/*
 *  FILE %ned/09/ned0932.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1997-12-04 21:10:05
 *  $Id: ned0932.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tk.h>
#include <tcl.h>

#include <stdio.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tk_set_color (
NED_Widget *nw,
GC *dGC,
int is_var,                     /* 1 -> colors are given as variable names  */
const char *fg_var,             /* variable of name that contains forground */
const char *bg_var)             /* e.g. txt_fg and background color         */
{
  Tcl_Interp *interp;
  Tk_Window new_win;
  GC newGC;
  XGCValues gcValues;
  XColor *xc_background;
  XColor *xc_foreground;
  Tk_Uid fg;
  Tk_Uid bg;
  char *ned= "ned";
  int rc= 0;

  interp= nw->interp;

  if (is_var)
  {
    fg_var= Tcl_GetVar2 (interp, ned, fg_var, TCL_GLOBAL_ONLY);
    bg_var= Tcl_GetVar2 (interp, ned, bg_var, TCL_GLOBAL_ONLY);
  }

  if (fg_var == (char *) 0) { rc= 1; fg_var= "white";   /* @@@ T2D */ }
  if (bg_var == (char *) 0) { rc= 1; bg_var= "red";     /* @@@ T2D */ }

  fg= Tk_GetUid (fg_var);
  bg= Tk_GetUid (bg_var);
  xc_foreground= Tk_GetColor (interp, new_win= nw->tkwin, fg);
  xc_background= Tk_GetColor (interp, new_win, bg);
  gcValues.font= Tk_FontId (nw->fontPtr);
  gcValues.foreground= xc_foreground->pixel;
  gcValues.background= xc_background->pixel;

  newGC= Tk_GetGC (new_win, GCForeground|GCBackground|GCFont, &gcValues);

  if (dGC != (GC *) 0)
  {
    if (*dGC != None && *dGC != (GC) 0) Tk_FreeGC (nw->display, *dGC);
    *dGC= newGC;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
GC ned_tk_setup_GC (NED_Widget *nw, int a)
{
  int num;
  int rc;
  char fg_col [10];
  char bg_col [10];
  const char *fg, *bg;
  Tcl_Interp *interp;
  char *ned= "ned";

  if (nw == (NED_Widget *) 0) return (GC) 0;

  if ((num= nw->attrib_cnt) >= NED_WIDGET_GC_CNT)
  {
    fprintf (stderr,
             "note: setup_GC attrib table full for {fg,bg}_%03d\n", a);
    return (GC) 0;
  }

  interp= nw->interp;

  sprintf (fg_col, "fg_%03d", a);
  if ((fg= Tcl_GetVar2 (interp, ned, fg_col, TCL_GLOBAL_ONLY)) == (char *) 0)
  {
    sprintf (fg_col, "col_%02d", a & 0x000F);
    fg= Tcl_GetVar2 (interp, ned, fg_col, TCL_GLOBAL_ONLY);
  }

  sprintf (bg_col, "bg_%03d", a);
  if ((bg= Tcl_GetVar2 (interp, ned, bg_col, TCL_GLOBAL_ONLY)) == (char *) 0)
  {
    sprintf (bg_col, "col_%02d", (a >> 4) & 0x000F);
    bg= Tcl_GetVar2 (interp, ned, bg_col, TCL_GLOBAL_ONLY);
  }

  rc= ned_tk_set_color (nw, &nw->attrib_GC [num], 0, fg, bg);
  nw->attrib_num [num]= a;
  nw->attrib_cnt++;

  if (rc == 1)
  {
    fprintf (stderr,
             "note: setup_GC no value found for {fg,bg}_%03d\n", a);
  }

  return nw->attrib_GC [num];
}
