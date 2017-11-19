/*
 *  FILE %ned/09/ned0922.c
 *
 *  call evaluation of a Tcl script and more Tcl interfacing
 *
 *  written:       1995-01-04
 *  latest update: 2000-12-09 13:17:40
 *  $Id: ned0922.c,v 1.10 2011/12/18 12:17:48 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

#include <stdio.h>
#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edctx.h"
#include "proto.h"

#ifdef USE_TCL
#include <gg/filename.h>
#include <tcl.h>
#include "edtcl.h"
#endif /* USE_TCL */

#ifdef USE_TK
#include <tk.h>
#include "edtk.h"
static Tk_Window ned_tk_main_window;
#include <X11/Xutil.h> /* used in _ned_tk_set_window_name */
#include <X11/Xatom.h>
#endif /* USE_TK */

/* ------------------------------------------------------------------------ */
extern struct NED_CONTEXT *ned_main_context;
extern struct WINDOWCTRL *aw;

#ifdef USE_TCL
Tcl_Interp *main_interp= (Tcl_Interp *) 0;
#endif /* USE_TCL */

static int window_cnt= 0;

/* ------------------------------------------------------------------------ */
int ned_tcl_startup (           /* initialize TCL by ned                    */
char *rc_names[],
char *tcl_glib)
{
#ifdef USE_TCL
  char *rc_name;
  int i;

  if ((main_interp= Tcl_CreateInterp ()) == (Tcl_Interp *) 0
      || Tcl_Init (main_interp) == TCL_ERROR
     )
  {
ERROR1:
    fprintf (stderr, "error initializing TCL subsystem!\n");
    ned_message_1 ("error initializing TCL subsystem!");
    return -1;
  }

  ned_tcl_register (main_interp);
  ned_tcl_preset (main_interp, tcl_glib);

  Tcl_CreateCommand (main_interp, "ned_main", ned_tcl_context,
    (ClientData) ned_main_context,
    (Tcl_CmdDeleteProc *) 0);

#ifdef USE_TK
  if (Tk_Init (main_interp) == TCL_ERROR) goto ERROR1;
  Tcl_CreateCommand (main_interp, "ned_current", ned_tk_current,
    (ClientData) 0,
    (Tcl_CmdDeleteProc *) 0);
#endif /* USE_TK */

  for (i= 0; (rc_name= rc_names [i]) != (char *) 0; i++)
    if (ned_tcl_run_file (rc_name) == TCL_OK) break;

#ifdef USE_TK
  ned_tk_main_window= Tk_MainWindow (main_interp);
  Tk_SetClass (ned_tk_main_window, "Ned");
  Tk_SetAppName (ned_tk_main_window, "ned");
  Tk_MakeWindowExist (ned_tk_main_window);
#endif /* USE_TK */

#else /* USE_TCL */
  rc_names;
  tcl_glib;
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tcl_run_file (char *rc_name)
{
#ifdef USE_TCL
  if (main_interp == (Tcl_Interp *) 0) return -1;

  return Tcl_EvalFile (main_interp, translate_logic_filename (rc_name));
#else
  rc_name;

  return 0;
#endif
}

/* ------------------------------------------------------------------------ */
int ned_tcl_stop ()                    /* stop TCL by ned                   */
{

#ifdef USE_TCL
  if (main_interp == (Tcl_Interp *) 0) return -1;
  Tcl_DeleteInterp (main_interp);
#endif /* USE_TCL */

  return 0;
}

/* ------------------------------------------------------------------------ */
int mac_call_tcl (char *tcl_script)
{
#ifdef USE_TCL
  int code;
  char *cp;
#endif /* USE_TCL */

  /**** ned_message_3 ("tcl macro: '", tcl_script, "'");        *****/
  /**** printf ("0922 tcl macro: '%s'\n", tcl_script);          ****/

#ifdef USE_TCL
  if (main_interp == (Tcl_Interp *) 0) return -1;

  code= Tcl_Eval (main_interp, tcl_script);
  if ((cp= main_interp->result) != (char *) 0 && *cp != 0)
    ned_message_2 ("Tcl result: ", cp);
#else
  ned_message_3 ("tcl macro: '", tcl_script, "'");
#endif /* !USE_TCL */

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_paste_tcl (char *tcl_script)
{
#ifdef USE_TCL
  int code;
  char *cp;
#else
#ifdef MSDOS
  tcl_script;
#endif /* MSDOS */
#endif /* !USE_TCL */

  /**** ned_message_3 ("tcl macro: '", tcl_script, "'");   *****/

#ifdef USE_TCL
  if (main_interp == (Tcl_Interp *) 0) return -1;

  code= Tcl_Eval (main_interp, tcl_script);
  if ((cp= main_interp->result) != (char *) 0 && *cp != 0)
  {
    ned_paste_string (cp, 0, (char *) 0, (char *) 0);
  }
#endif /* !USE_TCL */

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef USE_TCL
#ifdef USE_TK
static char cmd_buffer [1024];

int ned_tk_associate_window (struct WINDOWCTRL *wc)
{
  const char *argv [2];
  char path[40];
  int rc;

  sprintf (path, ".ned%02d", ++window_cnt);
  argv [0]= "ned";
  argv [1]= path;

  rc= _ned_tk_create_widget ((ClientData) ned_tk_main_window,
                             main_interp, 2, argv, wc);
  ned_tk_set_window_name (wc, wc->WC_title_short);

  return rc;
}

/* ------------------------------------------------------------------------ */
int ned_tk_delete_association (struct WINDOWCTRL *wc)
{
  NED_Widget *nw;

  if (wc == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) wc->wc_widget) == (NED_Widget *) 0
     ) return 0;        /* someone else was here before ... */

  sprintf (cmd_buffer, "remove_from_window_list %s", nw->window_path);
  mac_call_tcl (cmd_buffer);

  wc->wc_widget= (void *) 0;
  nw->ned_window= (struct WINDOWCTRL *) 0;

  _ned_tk_destroy_widget (nw);

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tk_set_window_name (struct WINDOWCTRL *wc, char *name)
{
  if (wc == (struct WINDOWCTRL *) 0) return -1;
  return _ned_tk_set_window_name (wc->wc_widget, name);
}

/* ------------------------------------------------------------------------ */
int _ned_tk_set_window_name (NED_Widget *nw, char *name)
{
#ifdef V1
  XTextProperty tp;

  if (nw != (NED_Widget *) 0
      && XStringListToTextProperty (&name, 1, &tp) != 0
     )
  {
    XSetWMName (nw->display, Tk_WindowId (nw->tkwin), &tp);
    XFree ((char *) tp.value);
    return 0;
  }
#endif

  if (nw != (NED_Widget *) 0)
  {
    char *path;

    path= nw->window_path;

    sprintf (cmd_buffer, "wm title %s {%s}; wm iconname %s {%s}",
             path, name, path, name);
    /*** fprintf (stderr, "0922: set_window_name name='%s'\n", name); ***/
    Tcl_Eval (nw->interp, cmd_buffer);

    sprintf (cmd_buffer, "add_to_window_list %s {%s}", path, name);
    Tcl_Eval (nw->interp, cmd_buffer);

#ifdef __COMMENT__
Note: add_to_window_list is a command in the main interpreters context
while the wm command could depend on the widget.
#endif /* __COMMENT__ */
    return 0;
  }

  return -1;
}

/* ------------------------------------------------------------------------ */
int ned_tk_import_selection ()
{
  NED_Widget *nw;
  int rc;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     ) return -1;

#ifdef __NOT_OK__ /* 1997-10-26  8:54:02 */
  ned_set_marker (aw, '0');
#endif /* __NOT_OK__ 1997-10-26  8:54:02 */

  rc= Tk_GetSelection (main_interp, nw->tkwin, XA_PRIMARY, XA_STRING,
                       ned_tk_imp_selection_procedure, (ClientData) nw);

#ifdef __JUNK__
  int offset1;
... dont use that section.

This sets the marked block to the newly imported selection and
claims the selection.  Importing the selection again could cause a
loop because the imported text is part of the exported selection as
well.  Also, claiming the selection upon import is not very intuitive
for the user.

  b_beg.wptr= marker[0].wptr;           /* T2D: eigene Funktion machen      */
  b_beg.ptr= marker[0].ptr;
  b_beg.offset= offset1;
  block_mode= BLOCK_MODE_standard;      /* switch to standard block mode    */

  p_blkend ();
#endif /* __JUNK__ */

  return rc;
}

/* ------------------------------------------------------------------------ */
int ned_tk_special_event (struct WINDOWCTRL *w, int what, int p1, int p2)
{
  NED_Widget *nw;
  char *event_str= (char *) 0;

  if (w == (struct WINDOWCTRL *) 0) w= aw;
  if (w == (struct WINDOWCTRL *) 0
      || (nw= w->wc_widget) == (NED_Widget *) 0
     ) return -1;

  switch (what)
  {
    case NED_TK_CMD_MOUSE_B2:
      if ((event_str= nw->cmd_right_button) == (char *) 0)
        event_str= "ned_mouse_b2";

      sprintf (cmd_buffer, "%s %d %d", event_str, p1, p2);
      mac_call_tcl (cmd_buffer);
      return 0;

    case NED_TK_CMD_WINS:
      if ((event_str= nw->cmd_WINS) == (char *) 0)
        event_str= "ned_cmd_wins";
      break;

    case NED_TK_CMD_MENU:
      if ((event_str= nw->cmd_MENU) == (char *) 0)
        event_str= "ned_cmd_menu";
      break;
  }

  if (event_str != (char *) 0) mac_call_tcl (event_str);

  return 0;
}

/* ------------------------------------------------------------------------ */
struct prompt_callback
{
  NED_field_editor_callback *cb;
  void *client_data;
  char *var_name;
} ;

/* ------------------------------------------------------------------------ */
/* create a Tk window to prompt for a string, e.g. in a file open dialog    */
/* see * for a discussion about a modified file open dialog                 */
int ned_tk_prompt_string (
char *label,
char *string,
char *help_cluster,
char *help_frame,
NED_field_editor_callback *cb,
void *client_data)
{
  char *var_name;               /* name of the temporary widget,            */
                                /* global variable and command !!!          */
  struct prompt_callback *cbs;

  if ((var_name= (char *) malloc (40)) == (char *) 0
      || (cbs= (struct prompt_callback *)
               calloc (sizeof (struct prompt_callback), 1))
               == (struct prompt_callback *) 0
     ) return -1;

  cbs->cb= cb;
  cbs->client_data= client_data;
  cbs->var_name= var_name;

  sprintf (var_name, "ned_tmp_%02d", ++window_cnt);
  sprintf (cmd_buffer,
           "ned_prompt_string %s {%s} %s %s {%s} {%s}",
           var_name, label, var_name, var_name,
           help_cluster, help_frame);

  Tcl_SetVar (main_interp, var_name, string, TCL_GLOBAL_ONLY);
  Tcl_CreateCommand (main_interp, var_name,
      (Tcl_CmdProc *)       ned_tk_cb_prompt_string,
      (ClientData)          cbs,
      (Tcl_CmdDeleteProc *) 0);

  Tcl_Eval (main_interp, cmd_buffer);

  return 0;
}

/* ------------------------------------------------------------------------ */
/* tcl syntax:  .... T2D                            */
int ned_tk_cb_prompt_string (
ClientData clientData,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct prompt_callback *cbs;
  const char *var_name;
  const char *var_value;

  if ((cbs= (struct prompt_callback *) clientData)
            == (struct prompt_callback *) 0
      || (var_name= cbs->var_name) == (char *) 0
     )
    return TCL_ERROR;

  var_value= Tcl_GetVar (interp, var_name, TCL_GLOBAL_ONLY);
  (*cbs->cb) ((char *) var_value, 0 /* T2D Not used! */, 0, cbs->client_data);

  Tcl_UnsetVar (interp, var_name, TCL_GLOBAL_ONLY);
  Tcl_DeleteCommand (interp, var_name);

  /** free_or_what (var_name);  duplicate free?? **/
  free_or_what (cbs);

  return TCL_OK;
}

/* ------------------------------------------------------------------------ */
int ned_tk_wc_window_action (struct WINDOWCTRL *wc, int what)
{
  NED_Widget *nw;
  char *action;
  char *path;

  switch (what)
  {
    case WC_action_deiconify:
      action= "wm deiconify %s;raise %s";
      break;
    case WC_action_iconify:
      action= "wm iconify %s";
      break;
    case WC_action_withdraw:
      action= "wm withdraw %s";
      break;
    default:
      return -1;
  }

  if (wc == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) wc->wc_widget) == (NED_Widget *) 0
      || (path= nw->window_path) == (char *) 0
     ) return -1;

  sprintf (cmd_buffer, action, path, path);
  Tcl_Eval (nw->interp, cmd_buffer);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_tk_aw_save_withdraw ()
{
  ned_save_reload (aw, WCTDM_no_change);
  return ned_tk_wc_window_action (aw, WC_action_withdraw);
}

/* ------------------------------------------------------------------------ */
int ned_tk_aw_withdraw ()
{
  return ned_tk_wc_window_action (aw, WC_action_withdraw);
}

/* ------------------------------------------------------------------------ */
int ned_tk_aw_iconify ()
{
  return ned_tk_wc_window_action (aw, WC_action_iconify);
}

/* ------------------------------------------------------------------------ */
int ned_tk_aw_deiconify ()      /* is this function really useful??? */
{
  return ned_tk_wc_window_action (aw, WC_action_deiconify);
}

/* ------------------------------------------------------------------------ */
/* tcl syntax:  ned_current <method> <pars>*                                */
int ned_tk_current (
ClientData clientData,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  NED_Widget *nw;

  if (aw == (struct WINDOWCTRL *) 0
      || (nw= (NED_Widget *) aw->wc_widget) == (NED_Widget *) 0
     )
    return TCL_ERROR;

  return ned_tk_widget_cmd ((ClientData) nw, interp, argc, argv);
}

/* ------------------------------------------------------------------------ */
int ned_tk_start_mode (struct WINDOWCTRL *wc)
{
  const char *start_mode;

  if ((start_mode= Tcl_GetVar2 (main_interp, "ned", "start_mode",
                     TCL_GLOBAL_ONLY)) == (char *) 0) return -1;
  
  if (abbrev ("withdrawn", start_mode, 1) == 1)
    ned_tk_wc_window_action (wc, WC_action_withdraw); else
  if (abbrev ("iconic", start_mode, 1) == 1)
    ned_tk_wc_window_action (wc, WC_action_iconify);
}
#endif /* USE_TK */
#endif /* USE_TCL */
