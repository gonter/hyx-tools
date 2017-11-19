/*
 *  FILE %ned/09/ned0938.c
 *
 *  NED's tcl application initialization
 *  register Tcl variables and links to them
 *  see also: %ned/00/ned0011.c
 *
 *  written:       1995-12-12 extracted from ned0923.c
 *  latest update: 1999-07-17 20:02:13
 *
 */

#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern int ned_horizontal_scroll_count;
extern int ned_vertical_scroll_count;
extern int word_wrap_count;
extern int oper_level;

extern char *default_cross_ref_template;
extern char *default_template_frame;
extern char *default_start_frame;
extern char *default_undef_frame;
extern char *default_cross_ref_prefix;
extern char *default_help_cluster;
extern char *default_help_open_file;
extern char *default_help_jump_to_line;
extern char *default_help_rename_frame;
extern char *default_help_cross_ref;

#define LIV(n,v) Tcl_LinkVar (interp, n, (char *) &v, TCL_LINK_INT)
#define LSV(n,v) Tcl_LinkVar (interp, n, (char *) &v, TCL_LINK_STRING)
#define SV2(n,v) Tcl_SetVar2 (interp, ned, n, v, TCL_GLOBAL_ONLY);

/* ------------------------------------------------------------------------ */
int ned_tcl_preset (Tcl_Interp *interp, char *tcl_glib)
{
  char *ned=    "ned";
  char *white=  "white";
  char *gold1=  "gold1";
  char *blue=   "#3d3cca";
  char *black=  "black";
  char *red=    "red";
  char *green=  "green";

  /* setting up the default colors of a NED_Widget      */
  /* setup default colors:                              */
  /*   element             color                        */
  SV2 ("fg_text",          green);
  SV2 ("bg_text",          black);
  SV2 ("fg_curs",          black);
  SV2 ("bg_curs",          green);
  SV2 ("fg_stat",          black);
  SV2 ("bg_stat",          white);
  SV2 ("fg_mark",          gold1);
  SV2 ("bg_mark",          red);
  SV2 ("fg_sel",           gold1);
  SV2 ("bg_sel",           "orange");

  SV2 ("fg_hidden",        blue);
  SV2 ("bg_hidden",        black);

  SV2 ("font",             "Rom11");
  SV2 ("glib",             tcl_glib);

  /* linked integer variables   */
  LIV ("ned_skip_horizontal",    ned_horizontal_scroll_count);
  LIV ("ned_skip_vertical",      ned_vertical_scroll_count);
  LIV ("ned_oper_level",         oper_level);
  LIV ("ned_ned_wrap_count",     word_wrap_count);

  /* linked string variables    */
  LSV ("ned_cross_ref_template", default_cross_ref_template);
  LSV ("ned_template_frame",     default_template_frame);
  LSV ("ned_start_frame",        default_start_frame);
  LSV ("ned_undef_frame",        default_undef_frame);
  LSV ("ned_cross_ref_prefix",   default_cross_ref_prefix);
  LSV ("ned_help_cluster",       default_help_cluster);
  LSV ("ned_help_open_file",     default_help_open_file);
  LSV ("ned_help_jump_to_line",  default_help_jump_to_line);
  LSV ("ned_help_rename_frame",  default_help_rename_frame);
  LSV ("ned_help_cross_ref",     default_help_cross_ref);

  return 0;
}
