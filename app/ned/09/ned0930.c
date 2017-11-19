/*
 *  FILE %ned/09/ned0930.c
 *
 *  NED's tk widget stuff
 *
 *  written:       1995-09-25
 *  latest update: 1997-10-26 10:21:20
 *
 */

#include <tk.h>
#include <tcl.h>

#include <syslog.h>
#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_tk_widget_delete (ClientData clientData)
{
  NED_Widget *nw= (NED_Widget *) clientData;

  _ned_tk_destroy_widget (nw);
}
