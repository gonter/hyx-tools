/*
 *  FILE %ned/09/ned0939.c
 *
 *  ned application context handler
 *
 *  <context> <subcommand> [-options] <pars>+
 *  the main context is ned_main
 *  see description for more details
 *
 *  written:       1995-12-12
 *  latest update: 1997-08-04  8:16:31
 *
 */

#include <tcl.h>

#include <string.h>
#include <sys/utsname.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#ifdef USE_TK
#include <tk.h>
#include "edtk.h"
#endif /* USE_TK */
#include "edctx.h"
#include "proto.h"

extern char NED_VERSION [];
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tcl_context (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  struct NED_CONTEXT *ctx;
  const char *sub_command;

  if ((ctx= (struct NED_CONTEXT *) client_data) == (struct NED_CONTEXT *) 0
      || argc <= 1
      || (sub_command= argv [1]) == (char *) 0
      || *sub_command == 0
     )
    return TCL_ERROR;

  if (strcmp ("sysname", sub_command) == 0)
  {
    struct utsname unm;
    uname (&unm);
    interp->result= unm.sysname;
    return TCL_OK;
  }

  if (strcmp ("machine", sub_command) == 0)
  {
    struct utsname unm;
    uname (&unm);
    interp->result= unm.machine;

    return TCL_OK;
  }

  if (abbrev ("version", sub_command, 3))
  {
    interp->result= NED_VERSION;
    return TCL_OK;
  }

  if (strcmp ("has_tk", sub_command) == 0)
  {
#ifdef USE_TK
    interp->result= "1";
#else
    interp->result= "0";
#endif
    return TCL_OK;
  }

#ifdef USE_TK
  if (abbrev ("active", sub_command, 3))
  {
    NED_Widget *nw;
    if (aw == (struct WINDOWCTRL *) 0
        || (nw= aw->wc_widget) == (NED_Widget *) 0
       )
      interp->result= "NIL";
    else
      interp->result= nw->window_path;

    return TCL_OK;
  }
#endif /* USE_TK */

  if (strcmp ("block", sub_command) == 0)
  {
    char *res2;

    if ((res2= ned_block_2_string ((char *) 0, 0, 0L, 0x0001)) == (char *) 0)
      return TCL_ERROR;

    Tcl_SetResult (interp, res2, TCL_DYNAMIC);
    return TCL_OK;
  }

  if (ned_add_context_list (ctx, argv+1, argc-1)) return TCL_OK;

  interp->result= "unknown method";

  return TCL_ERROR;
}
