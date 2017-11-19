/*
 *  FILE %ds/tcl/tcl_0010.c
 *
 *  TCL subroutine library
 *  url_register_handler schema procedure
 *
 *  written:       1996-03-18
 *  latest update: 1996-03-18 21:51:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <tcl.h>
#include <gg/filename.h>
#include <gg/url.h>
#include <gg/ggtcl.h>

/* ------------------------------------------------------------------------ */
struct XYZ
{
  Tcl_Interp *interp;
  char *cmd;
} ;

/* ------------------------------------------------------------------------ */
char *ggtcl_url_fetcher (
char *url,
void *client_data)
{
  struct XYZ *xyz;
  Tcl_Interp *interp;

  if ((xyz= (struct XYZ *) client_data) == (struct XYZ *) 0
      || (interp= xyz->interp) == (Tcl_Interp *) 0
      || xyz->cmd == (char *) 0
      || Tcl_VarEval (interp, xyz->cmd, " ", url, (char *) 0) != TCL_OK
     ) return (char *) 0;

  return strdup (interp->result);  
}

/* ------------------------------------------------------------------------ */
int ggtcl_register_url_handler (
ClientData client_data,
Tcl_Interp *interp,
int argc,
char *argv [])
{
  struct XYZ *xyz;
  int args_cnt= 0;
#define NEEDED_ARGS 2
  char *args [NEEDED_ARGS];
  char *arg;
  int do_strip= 1;
  int type= URL_TYPE_something;
  int i;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0
      || (xyz= (struct XYZ *) calloc (sizeof (struct XYZ), 1))
         == (struct XYZ *) 0
     )
    return TCL_ERROR;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];
    if (arg [0] == '-')
    {
      if (strcmp ("-nostrip", arg) == 0) do_strip= 0;
      if (strncmp ("-t", arg, 2) == 0)
        type= (int) get_parameter_value (arg+2);
    }
    else
    {
      if (args_cnt < NEEDED_ARGS)
      {
        args [args_cnt++]= arg;
      }
    }
  }

  if (args_cnt < NEEDED_ARGS)
  {
    Tcl_SetResult (interp, "invalid args", TCL_STATIC);
    return TCL_ERROR;
  }

  xyz->interp= interp;
  xyz->cmd= strdup (args [1]);

  if (url_register_handler (args [0], type, do_strip,
                            ggtcl_url_fetcher, (void *) xyz)
      == (struct URL_HANDLER *) 0)
    return TCL_ERROR;

  return TCL_OK;
}
