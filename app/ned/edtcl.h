/*
 *  FILE %ned/edtcl.h
 *
 *  various tcl stuff for NED
 *  see also: "edtk.h"
 *
 *  written:       1995-01-08
 *  latest update: 1998-08-18 15:56:47
 *  $Id: edtcl.h,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifndef __NED_edtcl__
#define __NED_edtcl__

#ifndef __TCL_command_pars__
# define __TCL_command_pars__ \
  ClientData clientData, Tcl_Interp *interp, int argc, const char *argv []
#endif /* ! __TCL_command_pars__ */

/* ------------------------------------------------------------------------ */
/* ned0923.c */ int ned_tcl_register (Tcl_Interp *interp);
/* ned0950.c */ int ned_tcl_cb_tag_rule (const char *dir_path, char **res_string,
                  char **res_type, void *client_data);

/* TCL commands procedures: ----------------------------------------------- */
/* ned0924.c */ int ned_tcl_execute_primitive   (__TCL_command_pars__);

/* ned0936.c */ int ned_tcl_edit_file           (__TCL_command_pars__);
/* ned0937.c */ int ned_tcl_edit_frame          (__TCL_command_pars__);
/* ned0937b.c */ int ned_tcl_edit_crf           (__TCL_command_pars__);
/* ned0939.c */ int ned_tcl_context             (__TCL_command_pars__);
/* ned0940.c */ int ned_tcl_set_markup          (__TCL_command_pars__);
/* ned0941.c */ int ned_tcl_paste_str           (__TCL_command_pars__);
/* ned0942.c */ int ned_tcl_submit_macro        (__TCL_command_pars__);
/* ned0943.c */ int ned_tcl_enter_entity        (__TCL_command_pars__);
/* ned0944.c */ int ned_tcl_jump_to_line        (__TCL_command_pars__);
/* ned0945.c */ int ned_tcl_eval_tag            (__TCL_command_pars__);
/* ned0946.c */ int ned_tcl_set_marker          (__TCL_command_pars__);
/* ned0946b.c */ int ned_tcl_activate_note      (__TCL_command_pars__);
                 int ned_tcl_define_note        (__TCL_command_pars__);
/* ned0947.c */ int ned_tcl_jmp_marker          (__TCL_command_pars__);
/* ned0948.c */ int ned_tcl_mac_define          (__TCL_command_pars__);
/* ned0949.c */ int ned_tcl_define_feature      (__TCL_command_pars__);
/* ned0950.c */ int ned_tcl_reg_tag_rule        (__TCL_command_pars__);
/* ned0951a.c */ int ned_tcl_def_abbrev         (__TCL_command_pars__);
/* ned0951b.c */ int ned_tcl_undef_abbrev       (__TCL_command_pars__);
/* ned0952a.c */ int ned_tcl_extract            (__TCL_command_pars__);

#endif /* __NED_edtcl__ */
