/*
 *  FILE %ds/tcl/tclreg01.c
 *
 *  Tcl subroutine library
 *
 *  written:       1996-03-17
 *  latest update: 1996-09-28 11:30:06
 *  $Id: tclreg01.c,v 1.2 2012/08/10 14:44:09 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <tcl.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
static N2P_t N2P_list [] =
{
  { "define_virtual_path",       (Tcl_CmdProc *) ggtcl_define_virtual_path       } ,
  { "read_virtual_path_table",   (Tcl_CmdProc *) ggtcl_read_virtual_path_table   } ,
  { "translate_virtual_name",    (Tcl_CmdProc *) ggtcl_translate_virtual_name    } ,
  { "virtual_filename",          (Tcl_CmdProc *) ggtcl_virtual_filename          } ,
  { "real_filename",             (Tcl_CmdProc *) ggtcl_real_filename             } ,
  { "filename_definition",       (Tcl_CmdProc *) ggtcl_filename_definition       } ,
  { "find_virtual_file",         (Tcl_CmdProc *) ggtcl_find_virtual_file         } ,
  { "set_dirinf",                (Tcl_CmdProc *) ggtcl_set_dirinf                } ,
  { "register_dirinf_generator", (Tcl_CmdProc *) ggtcl_register_dirinf_generator } ,
  { "register_url_handler",      (Tcl_CmdProc *) ggtcl_register_url_handler      } ,

  { (char *) 0,                  (Tcl_CmdProc *) 0                       }
} ;

/* ------------------------------------------------------------------------ */
int ggtcl_reg_filename_services (Tcl_Interp *interp)
{
  return ggtcl_reg_services (interp, N2P_list);
}
