/*
 *  FILE %ned/09/ned0923.c
 *
 *  NED's tcl application initialization
 *
 *  written:       1995-01-08
 *  latest update: 1999-05-01 18:49:51
 *
 */

#include <tcl.h>

#include <gg/ggtcl.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct NED_PRIMITIVES NED_PRIMITIVE_TABLE [];

/* ------------------------------------------------------------------------ */
static struct N2P NED_COMMAND_TABLE [] =
{
  { "edit_file",                        ned_tcl_edit_file                   },
  { "ned",                              ned_tcl_edit_file                   },
  { "edit_frame",                       ned_tcl_edit_frame                  },
  { "edit_crf",                         ned_tcl_edit_crf                    },

  { "set_markup",                       ned_tcl_set_markup                  },
  { "paste_str",                        ned_tcl_paste_str                   },
  { "enter_entity",                     ned_tcl_enter_entity                },

  { "jump_to_line",                     ned_tcl_jump_to_line                },
  { "tag",                              ned_tcl_eval_tag                    },
  { "set_marker",                       ned_tcl_set_marker                  },
  { "jmp_marker",                       ned_tcl_jmp_marker                  },

  { "submit_macro",                     ned_tcl_submit_macro                },
  { "define_macro",                     ned_tcl_mac_define                  },
  { "define_feature",                   ned_tcl_define_feature              },
  { "define_note",                      ned_tcl_define_note                 },
  { "note",                             ned_tcl_activate_note               },
  { "register_tag_rule",                ned_tcl_reg_tag_rule                },
  { "def_abbrev",                       ned_tcl_def_abbrev                  },
  { "undef_abbrev",                     ned_tcl_undef_abbrev                },

  { (char *) 0,                         (Tcl_CmdProc *) 0                   }
} ;

/* ------------------------------------------------------------------------ */
int ned_tcl_register (Tcl_Interp *interp)
{
  int i;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  for (i= 0;; i++)
  {
    if (NED_PRIMITIVE_TABLE [i].NP_name == (char *) 0) break;

    Tcl_CreateCommand (interp,
                            NED_PRIMITIVE_TABLE [i].NP_name,
      (Tcl_CmdProc *)       ned_tcl_execute_primitive,
      (ClientData)          NED_PRIMITIVE_TABLE [i].NP_func,
      (Tcl_CmdDeleteProc *) 0);
  }

  ggtcl_reg_services (interp, NED_COMMAND_TABLE);
  ggtcl_reg_filename_services (interp);
  ggtcl_reg_hyx_services (interp);

  return TCL_OK;
}
