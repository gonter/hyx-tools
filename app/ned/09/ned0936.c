/*
 *  FILE %ned/09/ned0936.c
 *
 *  edit a file
 *
 *  Docs: edit_file [-opts] [filename]
 *
 *  written:       1995-11-27
 *  latest update: 2001-02-11 21:28:19
 *  $Id: ned0936.c,v 1.5 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern int ned_werr_dont_complain;

/* ------------------------------------------------------------------------ */
int ned_tcl_edit_file (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  int rc;
  int flags= NED_OPENF_HISTORY|NED_OPENF_REDRAW;
  char *fnm_allocated= (char *) 0;
  const char *fnm= (char *) 0;
  const char *arg;
  const char *help_cluster= (char *) 0;
  const char *help_frame= (char *) 0;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];
    if (strncmp (arg, "-cl", 3) == 0) help_cluster= arg + 3;                else
    if (strncmp (arg, "-fr", 3) == 0) help_frame= arg + 3;                  else
    if (abbrev ("-nocomplain",arg, 5)) ned_werr_dont_complain= 1;           else
    if (abbrev ("-exists",    arg, 2)) flags |= NED_OPENF_EXISTS;           else
    if (abbrev ("-nohistory", arg, 3)) flags ^= NED_OPENF_HISTORY;          else
    if (abbrev ("-prompt",    arg, 2)) flags |= NED_OPENF_PROMPT;           else
    if (abbrev ("-norelativepath", arg, 5)) flags ^= NED_OPENF_NO_REL_PATH; else
    if (abbrev ("-noctx", arg, 5)) flags ^= NED_OPENF_NO_REL_PATH;          else
    if (abbrev ("-sgml", arg, 3)) flags |= NED_OPENF_SGML;                  else
    if (abbrev ("-ascii", arg, 3)) flags &= ~NED_OPENF_SGML;                else
    fnm= arg;
  }

  if (fnm == (char *) 0)
  {
    if ((fnm_allocated= set_tmp_filename ((char *) 0, (char *) 0)) == (char *) 0)
    {
      interp->result= "no file specified";
      return TCL_ERROR;
    }
    fnm= (const char *) fnm_allocated;
  }

  if (ned_open_file (fnm, help_cluster, help_frame, flags) == 0)
  {
    rc= TCL_OK;
  }
  else
  {
    interp->result= "could not edit";
    rc= TCL_ERROR;
  }

  if (fnm_allocated != (char *) 0) free (fnm_allocated);

  return rc;
}
