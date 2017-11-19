/*
 *  FILE %ned/09/ned0946b.c
 *
 *  activate a note
 *
 *  note <area> [<topic>]
 *
 *  written:       1998-08-18
 *  latest update: 1998-08-18 15:42:31
 *  $Id: ned0946b.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <gg/strings.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
static int _get_topic_and_options (
int argc,
const char *argv[],
const char **area,
const char **topic,
int *create_mode,
int *memorize)
{
  int cnt;
  const char *arg;

  *area= *topic= (char*) 0;
  *create_mode= *memorize= 0;

  for (cnt= 1; cnt < argc; cnt++)
  {
    arg= argv [cnt];
    if (arg [0] == '-')
    {
      if (abbrev ("-memorize", arg, 4) == 1) *memorize= 1;
      else if (abbrev ("-create", arg, 3) == 1) *create_mode= 1;
      else return -1;
    }
    else
    {
      if (*area == (char *) 0) *area= arg;
      else if (*topic == (char *) 0) *topic= arg;
      else return -1;
    }
  }

  return (*area == (char *) 0) ? -1 : 0;
}

/* ------------------------------------------------------------------------ */
int ned_tcl_activate_note (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */
  const char *area, *topic;
  int create_mode, memorize;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (_get_topic_and_options (argc, argv, &area, &topic,
         &create_mode, &memorize) != 0)
  {
    interp->result= "invalid arguments";
    return TCL_ERROR;
  }

  ned_find_note_cluster (area, topic, create_mode, memorize);

  return TCL_OK;
}

/* ------------------------------------------------------------------------ */
int ned_tcl_define_note (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
#ifdef MSDOS
  client_data;
#endif /* MSDOS */
  const char *area, *topic;
  int create_mode, memorize;

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (_get_topic_and_options (argc, argv, &area, &topic,
         &create_mode, &memorize) != 0)
  {
    interp->result= "invalid arguments";
    return TCL_ERROR;
  }

  ned_define_note_cluster (area, topic, create_mode, memorize);

  return TCL_OK;
}
