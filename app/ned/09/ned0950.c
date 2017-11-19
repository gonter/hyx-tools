/*
 *  FILE %ned/09/ned0950.c
 *
 *  register a tagging rule
 *
 *  register_tag_rule type rule_proc
 *  rule_proc string
 *
 *  written:       1996-11-10
 *  latest update: 1999-04-25 16:35:17
 *  $Id: ned0950.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <tcl.h>
#include "ed.h"
#include "edctx.h"
#include "edtcl.h"
#include "proto.h"

extern struct NED_CONTEXT *ned_main_context;

/* ------------------------------------------------------------------------ */
struct XYZ
{
  Tcl_Interp *interp;
  char *type;
  char *cmd;
} ;

/* ------------------------------------------------------------------------ */
int ned_tcl_cb_tag_rule (               /* tagging rule call back           */
const char *dir_path,
char **res_string,
char **res_type,
void *client_data)
{
  struct XYZ *xyz;
  char *res;
  Tcl_Interp *interp;

  if ((xyz= (struct XYZ *) client_data) == (struct XYZ *) 0
      || (interp= xyz->interp) == (Tcl_Interp *) 0
      || xyz->cmd == (char *) 0
      || Tcl_VarEval (interp, xyz->cmd, " ", dir_path, (char *) 0) != TCL_OK
      || (res= interp->result) == (char *) 0
      || *res == 0
     ) return 0;

  *res_string= strdup (interp->result);  
  *res_type= strdup (xyz->type);

  return 1;
}

/* ------------------------------------------------------------------------ */
int ned_tcl_reg_tag_rule (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  struct XYZ *xyz;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0
      || argc != 3
      || (xyz= (struct XYZ *) calloc (sizeof (struct XYZ), 1))
         == (struct XYZ *) 0
     )
    return TCL_ERROR;

  xyz->interp= interp;
  xyz->type= strdup (argv [1]);
  xyz->cmd= strdup (argv [2]);

  if (ned_add_tag_rule (ned_main_context, argv [2],
                        ned_tcl_cb_tag_rule, (void *) xyz) != 0)
    return TCL_ERROR;

  return TCL_OK;
}
