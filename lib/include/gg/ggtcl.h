/*
 *  include FILE <gg/ggtcl.h>
 *
 *  GG's Tcl libarary
 *  - registration procedures
 *  - command procedures
 *
 *  written:       1996-03-17
 *  latest update: 1996-09-28 11:35:38
 *  $Id: ggtcl.h,v 1.2 2012/08/10 14:44:09 gonter Exp $
 *
 */

#ifndef __GG_ggtcl__
#define __GG_ggtcl__

#include <gg/floskel.h>

/* ------------------------------------------------------------------------ */
struct N2P
{
  char *cmd;
  Tcl_CmdProc *prc;
} ;

typedef struct N2P N2P_t;

#define __TCL_CMDPROC__  ClientData client_data, Tcl_Interp *interp, \
                         int argc, char *argv []
/* registration procedures: ----------------------------------------------- */
int ggtcl_reg_services (Tcl_Interp *interp, struct N2P *service_table);
int ggtcl_reg_filename_services (Tcl_Interp *interp);
int ggtcl_reg_hyx_services (Tcl_Interp *interp);

/* command procedures: ---------------------------------------------------- */

/* filename services */
int ggtcl_template (__TCL_CMDPROC__);
int ggtcl_translate_virtual_name (__TCL_CMDPROC__);
int ggtcl_read_virtual_path_table (__TCL_CMDPROC__);
int ggtcl_define_virtual_path (__TCL_CMDPROC__);
int ggtcl_virtual_filename (__TCL_CMDPROC__);
int ggtcl_real_filename (__TCL_CMDPROC__);
int ggtcl_filename_definition (__TCL_CMDPROC__);
int ggtcl_find_virtual_file (__TCL_CMDPROC__);
int ggtcl_set_dirinf (__TCL_CMDPROC__);
int ggtcl_register_dirinf_generator (__TCL_CMDPROC__);
int ggtcl_register_url_handler (__TCL_CMDPROC__);

/* helpers */
char *ggtcl_dirinf_generator (char *dir_path, void *client_data);
char *ggtcl_url_fetcher (char *url, void *client_data);

/* hyx services */
int ggtcl_hyx_set_color_code (__TCL_CMDPROC__);

#endif /* __GG_ggtcl__ */
