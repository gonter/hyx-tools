/*
 *  FILE %ned/09/ned0942.c
 *
 *  submit a macro
 *
 *  submit_macro <str>+
 *
 *  written:       1996-06-09
 *  latest update: 1996-12-12 21:02:53
 *  $Id: ned0942.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_submit_macro (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  int opts= 1;
  const char *arg;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 1)
  {
    interp->result= "no string given";
    return TCL_ERROR;
  }

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];
    if (opts && *arg == '-')
    {
      if (strcmp (arg, "--") == 0) opts= 0; else
      if (strcmp (arg, "-vi") == 0)
      {
        vi_on ();
      }
      else
      if (strcmp (arg, "-ins") == 0)
      {
        vi_ins ();
      }
      else
      if (strcmp (arg, "-VI") == 0)
      {
        vi_on ();
        vi_mode ();
      }
      else
      if (strcmp (arg, "-ws") == 0)
      {
        wordstar_mode ();
      }
    }
    else
    {
      ned_submit_macro (arg);
    }
  }

  p_refresh ();

  return TCL_OK;
}
