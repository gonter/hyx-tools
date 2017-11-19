/*
 *  FILE %ned/edtk.h
 *
 *  various tk stuff for NED
 *  - macros
 *
 *  written:       1995-09-25
 *  latest update: 1999-05-06 16:48:47
 *  $Id: edtk.h,v 1.6 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifndef __NED_edtk__
#define __NED_edtk__

#ifndef __TCL_command_pars__
# define __TCL_command_pars__ \
  ClientData clientData, Tcl_Interp *interp, int argc, const char *argv []
#endif /* ! __TCL_command_pars__ */

/* ------------------------------------------------------------------------ */
void NED_tk_key_pressed (ClientData clientData, XEvent *eventPtr);

#define NED_WIDGET_GC_CNT 24

/* NED editor widget ------------------------------------------------------ */
typedef struct
{
  /* standard widget-Tk-Tcl-interfacing pointers and hooks                  */
  Tk_Window tkwin;                      /* window for that particular item  */
  Tk_Window sc_win;                     /* scroll bar window                */
  Display *display;                     /* display where this widget is     */
  Tcl_Interp *interp;                   /* parrent TCL interpreter          */
  Tcl_Command widgetCmd;                /* command name for this widget     */
  char *window_path;                    /* TK window path name              */

  /* graphics contexts                                                      */
  GC normalTextGC;                      /* Perfectly Normal Text            */
  GC cursedTextGC;                      /* text colour at cursor position   */
  GC StatusLineGC;                      /* status line                      */
  GC markedTextGC;                      /* block marker colour              */
  GC selectedTextGC;                    /* block marker colour with select  */
  GC hiddenTextGC;                      /* text that should not be shown    */

  int selection_active;                 /* flag */

  GC attrib_GC [NED_WIDGET_GC_CNT];
  int attrib_num [NED_WIDGET_GC_CNT];
  int attrib_cnt;                       /* number of entries in this table  */

  /* derived from font properties                                           */
  Tk_Font fontPtr;                      /* Tk 8.0 font object               */
  int char_width;                       /* character cell width in pixels   */
  int char_ascent;                      /* number of pixels top to baseline */
  int line_height;                      /* character cell height in pixels  */

  int num_x_pixels;                     /* size of window in pixels         */
  int num_y_pixels;

  int num_x_pix_offset;                 /* extra space on the left side     */
  int num_x_pix_extra;                  /* extra space on the right side    */
  int num_y_pix_offset;                 /* extra space on top               */
  int num_y_pix_extra;                  /* extra space on the bottom        */

  /* context sensitive command handlers; executed on certain events         */
  char *cmd_MENU;                       /* click on MENU button             */
  char *cmd_WINS;                       /* click on WINS button             */
  char *cmd_right_button;               /* click with right mouse button    */

  struct WINDOWCTRL *ned_window;        /* association with NED window desc.*/
  char *tcl_on_lost_selection;  /* XXX window-path */
} NED_Widget; /* IS_STRUCT */

/* macros: ---------------------------------------------------------------- */
#define ned_get_x_pos(nw,x)     ((x) * (nw)->char_width)
#define ned_get_y_pos(nw,y)     ((y) * (nw)->line_height + (nw)->char_ascent)

#define ned_get_cx_pos(nw,px)   ((px) / ((nw)->char_width))
#define ned_get_cy_pos(nw,py)   ((py) / (nw)->line_height)

#define ned_get_blk_GC(nw) (((nw)->selection_active) \
                            ? (nw)->selectedTextGC : (nw)->markedTextGC)

/* types of X events being processed in a NED editor widget */
#define NED_WIDGET_EVENT_MASK   \
  KeyPressMask                  \
  | ButtonPressMask             \
  | ButtonReleaseMask           \
  | PointerMotionMask           \
  | PointerMotionHintMask       \
  | ExposureMask                \
  | StructureNotifyMask         \
  | FocusChangeMask

/* prototypes: ------------------------------------------------------------ */
int ned_tk_associate_window (struct WINDOWCTRL *wc);

/* ned0922.c */ int _ned_tk_set_window_name (NED_Widget *nw, char *name);
                int ned_tk_setup_event (struct WINDOWCTRL *w, int what);
                int ned_tk_cb_prompt_string (ClientData clientData,
                  Tcl_Interp *interp, int argc, char *argv []);
                int ned_tk_current (__TCL_command_pars__);
                int ned_tk_aw_save_withdraw (void);
                int ned_tk_aw_withdraw (void);
                int ned_tk_aw_iconify (void);
                int ned_tk_aw_deiconify (void);
                int ned_tk_start_mode (struct WINDOWCTRL *wc);

/* ned0925.c */ int _ned_tk_create_widget (
                  __TCL_command_pars__, struct WINDOWCTRL *wc);
                int ned_tk_set_font (NED_Widget *nw, const char *font_name);
                int ned_tk_set_geometry (NED_Widget *nw);
                int ned_tk_setup_special (struct WINDOWCTRL *w, int what,
                  char *str);
                int _ned_tk_setup_special (NED_Widget *nw, int what,
                  const char *str);
                int ned_tk_window_dock (struct WINDOWCTRL *w1,
                  struct WINDOWCTRL *w2, int pos);
/* ned0926.c */ int ned_tk_create_widget (__TCL_command_pars__);
/* ned0927.c */ int ned_tk_configure (Tcl_Interp *interp, NED_Widget *nw,
                  int argc, const char *argv [], int flags);
/* ned0928.c */ int _ned_tk_destroy_widget (NED_Widget *nw);
/* ned0929.c */ int ned_tk_widget_cmd (__TCL_command_pars__);
/* ned0930.c */ void ned_tk_widget_delete (ClientData clientData);
/* ned0931.c */ void ned_tk_event_procedure (ClientData clientData,
                  XEvent *eventPtr);
/* ned0932.c */ int ned_tk_set_color (NED_Widget *nw, GC *dGC,
                  int is_var, const char *fg_var, const char *bg_var);
                GC ned_tk_setup_GC (NED_Widget *nw, int a);
/* ned0933.c */ int ned_tk_redraw_window (NED_Widget *nw, int pxa, int pya,
                                                          int pxb, int pyb);
/* ned0934.c */ int ned_tk_exp_selection_procedure (ClientData clientData,
                  int offset, char *buffer, int maxBytes);
                void ned_tk_lost_selection (ClientData cd);
                int ned_tk_block_export_flag (int flag);
/* ned0935.c */ int ned_tk_imp_selection_procedure (ClientData clientData,
                  Tcl_Interp *interp, char *buffer);

/* %ned/unix/tk2.c */
GC ned_tk_get_GC (NED_Widget *nw, int a);
int tk_draw_string (struct WINDOWCTRL *w, int what, int x, int y, char *s);

#endif /* __NED_edtk__ */
