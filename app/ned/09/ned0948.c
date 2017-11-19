/*
 *  FILE %ned/09/ned0948.c
 *
 *  define a NED macro
 *
 *  define_macro <num> <type> <str>+
 *
 *  written:       1996-11-03
 *  latest update: 1996-11-03 18:27:27
 *  $Id: ned0948.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tcl.h>

#include <stdio.h>
#include <gg/dpp.h>
#include "ed.h"
#include "edtcl.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_tcl_mac_define (
ClientData client_data,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  int i;
  int mac_type;
  long mac_num;
  char mac_number [10];

#ifdef MSDOS
  client_data;
#endif /* MSDOS */

  if (interp == (Tcl_Interp *) 0) return TCL_ERROR;

  if (argc <= 3)
  {
    interp->result= "no string given";
    return TCL_ERROR;
  }

  mac_num= get_parameter_value (argv [1]);
  switch (argv [2][0])
  {
    case 't': case 'T':
      mac_type= MPt_tcl;
      break;
    default:
      mac_type= MPt_key_sequence;
      break;
  }

  for (i= 3; i < argc; i++)
  {
    sprintf (mac_number, "%ld", mac_num++);
    mac_definition (mac_number, argv [i], mac_type);
  }

  return TCL_OK;
}
