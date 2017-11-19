/*
 *  FILE %ned/09/ned0937.c
 *
 *  edit a frame
 *
 *  DOCU: edit_frame [-opts] [cluster [frame]*]
 *
 *  no cluster name:    %cl0
 *  no frame name:      $$root
 *
 *  written:       1995-11-28
 *  latest update: 1997-10-26 10:23:42
 *  $Id: ned0937.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern char *default_template_frame;
extern char *default_undef_frame;
extern char *default_start_frame;
extern int ned_werr_dont_complain;

/* ------------------------------------------------------------------------ */
int ned_tcl_edit_frame (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  int frames_edited= 0;                 /* number of frames edited          */
  int search_mode= 0x0002;
  int format= FMT_SGML;
  const char *arg;
  const char *cluster_name= (char *) 0;
  const char *template= (char *) 0;
  const char *alternate= (char *) 0;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  for (i= 1; i < argc; i++)
  {
    arg= argv [i];

    if (arg [0] == '-')
    {
      if (abbrev ("-global", arg, 3)) search_mode |= 0x0001; else
      if (abbrev ("-exists", arg, 3)) search_mode ^= 0x0002; else
      if (abbrev ("-nocomplain",arg, 5)) ned_werr_dont_complain= 1; else
      if (strncmp ("-t", arg, 2) == 0)
      {
        template= arg + 2;
        if (*template == 0) template= default_template_frame;
        search_mode |= 0x0002;
      } else
      if (strncmp ("-a", arg, 2) == 0)
      {
        alternate= arg + 2;
        if (*alternate == 0) alternate= default_undef_frame;
        search_mode ^= 0x0002;
      }
    }
    else
    {
      if (cluster_name == (char *) 0) cluster_name= arg;
      else
      {
        if (ned_activate_cl_fr (cluster_name, arg, search_mode, format,
                                template, alternate)
            == (struct FRAMECTRL *) 0)
        {
ERROR:
          interp->result= "could not edit";
          return TCL_ERROR;
        }

        frames_edited++;
      }
    }
  }

  if (!frames_edited
      && ned_activate_cl_fr (cluster_name, default_start_frame, search_mode,
                             format, template, alternate)
          == (struct FRAMECTRL *) 0
     ) goto ERROR;

  return TCL_OK;
}
