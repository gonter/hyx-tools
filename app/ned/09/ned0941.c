/*
 *  FILE %ned/09/ned0941.c
 *
 *  paste one or more strings
 *
 *  duco: paste_string [<-opts>|<str>]+
 *
 *  written:       1996-06-09
 *  latest update: 1996-07-14 19:32:21
 *  $Id: ned0941.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_tcl_paste_str (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  const char *arg;
  int ai_mode= 0;

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
    if (strcmp (arg, "-ai")    == 0) ai_mode= wdw_off (aw); else
    if (strcmp (arg, "-noai")  == 0) ai_mode= 0; else
    ned_paste_string (arg, ai_mode, (char *) 0, (char *) 0);
  }

  return TCL_OK;
}
