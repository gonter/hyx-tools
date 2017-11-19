/*
 *  FILE %ned/09/ned0925.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1999-05-30  8:53:11
 *  $Id: ned0925.c,v 1.6 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tk.h>
#include <tcl.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"
#include <X11/Xatom.h>

/* ------------------------------------------------------------------------ */
/* tcl syntax:  ned <window_path> (<opt> <val>)*                            */
int _ned_tk_create_widget (
ClientData clientData,
Tcl_Interp *interp,
int argc,
const char *argv [],
struct WINDOWCTRL *wc)
{
  Tk_Window tkwin= (Tk_Window) clientData;
  Tk_Window new_win;
  NED_Widget *nw;
  char *path_name;
  const char *my_name;

  my_name= argv [1];

  if (tkwin == (Tk_Window) 0)
  {
    fprintf (stderr, "tkwin not initialized!  Is Tk propperly installed?\n");
    exit (0);
  }

  if ((new_win= Tk_CreateWindowFromPath (interp, tkwin, my_name, ""))
        == (Tk_Window) 0
      || (nw= (NED_Widget *) calloc (sizeof (NED_Widget), 1))
           == (NED_Widget *) 0
     )
  {
    return TCL_ERROR;
  }

  /* create one-to-one association between widget and window control */
  /* T2D: create a many-to-many association for future use */
  nw->ned_window= wc;
  wc->wc_widget= nw;

  nw->window_path= strdup (my_name);
  nw->tkwin= new_win;
  nw->display= Tk_Display (new_win);
  nw->interp= interp;
  nw->widgetCmd= Tcl_CreateCommand (
                   interp,
                   path_name= Tk_PathName (new_win),
                   ned_tk_widget_cmd,
                   (ClientData) nw,
                   ned_tk_widget_delete);

  nw->num_x_pix_extra= 20;

/* @@@ BEGIN NEW */
  {
    char *sc_name;
    char *sc_yview;
    char *sc_cmds [6];
    int rc;
    Tk_Window sc_win;

    sc_name= (char *) malloc (strlen (my_name) + 4);
    sc_yview= (char *) malloc (strlen (my_name) + /*8*/ 24);
    sprintf (sc_name, "%s.sb", my_name);
    sprintf (sc_yview, "%s yview", my_name);

    sc_cmds [0]= "";
    sc_cmds [1]= sc_name;
    sc_cmds [2]= "-command";
    sc_cmds [3]= sc_yview;
    sc_cmds [4]= "-takefocus";
    sc_cmds [5]= "0";

    rc= Tk_ScrollbarCmd ((ClientData) new_win, interp, 6, sc_cmds);
    nw->sc_win= sc_win= Tk_NameToWindow (interp, sc_name, new_win);

    free (sc_name);
    free (sc_yview);
  }
/* @@@ END NEW */

  Tk_SetClass (new_win, "Ned");

  if (ned_tk_set_font (nw,
            Tcl_GetVar2 (interp, "ned", "font", TCL_GLOBAL_ONLY)) != 0
      || ned_tk_configure (interp, nw, argc-2, argv+2, 0) != TCL_OK
     )
  {
    Tk_DestroyWindow (new_win);
    fprintf (stderr, "NED 0925 config err: '%s'\n", interp->result);
    return TCL_ERROR;
  }

  Tk_MapWindow (new_win);
  Tk_MapWindow (nw->sc_win);

  Tk_CreateEventHandler (new_win, NED_WIDGET_EVENT_MASK,
                         ned_tk_event_procedure, (ClientData) nw);

  Tk_CreateSelHandler (new_win, XA_PRIMARY, XA_STRING,
                       ned_tk_exp_selection_procedure, (ClientData) nw,
                       XA_STRING);

  interp->result= path_name;

  return TCL_OK;
}

/* ------------------------------------------------------------------------ */
int ned_tk_set_font (NED_Widget *nw, const char *font_name)
{
  Tk_Font tkf;
  Tk_Window new_win;
  Tcl_Interp *interp;
  Tk_FontMetrics fm;
  int width;
  struct WINDOWCTRL *wc;

  /* Font Stuff */
  if (font_name == (char *) 0
      || (tkf= Tk_GetFont (nw->interp, nw->tkwin, Tk_GetUid (font_name)))
              == (Tk_Font) 0
      || (wc= nw->ned_window) == (struct WINDOWCTRL *) 0
      || (new_win= nw->tkwin) == (Tk_Window) 0
      || (interp= nw->interp) == (Tcl_Interp *) 0
     ) return -1;

  Tk_GetFontMetrics (tkf, &fm);
  Tk_MeasureChars (tkf, "0", 1, -1, 0x00, &width);

  nw->fontPtr= tkf;
  nw->line_height= fm.linespace;
  nw->char_ascent= fm.ascent;
  nw->char_width= width;

/********************
  printf (
"ned0925.c: NED_widget: nw=0x%08lX tkf=0x%08lX char_width=%d (%d) line_height=%d\n",
            nw, tkf, width, nw->char_width, fm.linespace);
********************/

  nw->num_x_pixels= (wc->bx + 1) * nw->char_width
                    + nw->num_x_pix_offset + nw->num_x_pix_extra;
  nw->num_y_pixels= (wc->by + 1) * nw->line_height
                    + nw->num_y_pix_offset + nw->num_y_pix_extra;

  /* Graphics Contexts: normal text and such                                */
  /* defaults are set by ned_tcl_preset                                     */
  ned_tk_set_color (nw, &nw->normalTextGC, 1, "fg_text",   "bg_text");
  ned_tk_set_color (nw, &nw->cursedTextGC, 1, "fg_curs",   "bg_curs");
  ned_tk_set_color (nw, &nw->StatusLineGC, 1, "fg_stat",   "bg_stat");
  ned_tk_set_color (nw, &nw->markedTextGC, 1, "fg_mark",   "bg_mark");
  ned_tk_set_color (nw, &nw->selectedTextGC,1,"fg_sel",    "bg_sel");
  ned_tk_set_color (nw, &nw->hiddenTextGC, 1, "fg_hidden", "bg_hidden");
  nw->attrib_cnt= 0;

  ned_tk_set_geometry (nw);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tk_set_geometry (NED_Widget *nw)
{
  int y_off;

  /* change geometry of parent and slave windows */
  Tk_GeometryRequest (nw->tkwin, nw->num_x_pixels, nw->num_y_pixels);
  y_off= nw->line_height * 3;   /* check: possibly not always ! */
  Tk_MoveResizeWindow (nw->sc_win,
                       nw->num_x_pixels - nw->num_x_pix_extra, y_off,
                       nw->num_x_pix_extra, nw->num_y_pixels - y_off);

  return 0;
}

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tk_setup_special (struct WINDOWCTRL *w, int what, char *str)
{
  if (w == (struct WINDOWCTRL *) 0) w= aw;
  if (w == (struct WINDOWCTRL *) 0) return -1;

  return _ned_tk_setup_special (w->wc_widget, what, str);
}

/* ------------------------------------------------------------------------ */
int _ned_tk_setup_special (NED_Widget *nw, int what, const char *str)
{
  char *s= (char *) 0;

  if (nw == (NED_Widget *) 0) return -1;

  if (str != (char *) 0) s= strdup (s);

  switch (what)
  {
    case NED_TK_CMD_MOUSE_B2:
      nw->cmd_right_button= s;
      break;

    case NED_TK_CMD_WINS:
      nw->cmd_WINS= s;
      break;

    case NED_TK_CMD_MENU:
      nw->cmd_MENU= s;
      break;

    default:
      free_or_what (s);
      return -1;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tk_window_dock (
struct WINDOWCTRL *w1,
struct WINDOWCTRL *w2,
int pos)
{
  NED_Widget *nw1, *nw2;
  Tk_Window   tw1,  tw2;
  int x_p, y_p, x_w, y_w;
  char buffer [80];

  if (w1 == (struct WINDOWCTRL *) 0) w1= aw;
  if (w1 == (struct WINDOWCTRL *) 0
      || w2 == (struct WINDOWCTRL *) 0
      || (nw1= w1->wc_widget) == (NED_Widget *) 0
      || (nw2= w2->wc_widget) == (NED_Widget *) 0
      || (tw1= nw1->tkwin) == (Tk_Window) 0
     ) return -1;

  switch (pos)
  {
    default:
      x_p= Tk_X (tw1);
      x_w= nw1->num_x_pixels;
      y_w= 250;
      y_p= Tk_Y (tw1) - y_w - 40;
      break;
  }

  if (y_p < 23)
  { /* stacked window would be over the top => move lower down */
    sprintf (buffer, "wm geometry %s %dx%d+%d+%d\n",
             nw1->window_path, x_w, nw1->num_y_pixels, x_p,
             Tk_Y(tw1) - y_p + 23);
    /*** printf ("0925: %s\n", buffer); ***/
    Tcl_Eval (nw1->interp, buffer);
    y_p= 23;
  }

  sprintf (buffer, "wm geometry %s %dx%d+%d+%d\n",
           nw2->window_path, x_w, y_w, x_p, y_p);
  /*** printf ("0925: %s\n", buffer); ***/
  Tcl_Eval (nw2->interp, buffer);

  return 0;
}
