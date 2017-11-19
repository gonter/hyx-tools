/*
 *  FILE %ned/09/ned0927.c
 *
 *  NED's tk widget stuff
 *
 *  implements the NED widget command
 *  - description
 *
 *  written:       1995-09-25
 *  latest update: 1997-12-04 23:09:05
 *  $Id: ned0927.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tk.h>
#include <tcl.h>

#include "ed.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
#ifdef __NOT_USED__
... maybe ...
static Tk_ConfigSpec configSpecs [] =
{
  { TK_CONFIG_END, (char *) 0, (char *) 0, (char *) 0, (char *) 0, 0, 0     }
} ;
#endif /* __NOT_USED__ */

/* ------------------------------------------------------------------------ */
int ned_tk_configure (
Tcl_Interp *interp,
NED_Widget *nw,
int argc,
const char *argv [],
int flags)
{
  const char *str;
  const char *par;
  int geometry_changed= 0;

  if (interp == (Tcl_Interp *) 0
      || nw == (NED_Widget *) 0
     ) return TCL_ERROR;

  while (argc > 0)
  {
    str= *argv++;
    argc--;

    if (argc <= 0) goto ERR;
    par= *argv++;
    argc--;

    if (strcmp (str, "-font") == 0)
    {
      if (ned_tk_set_font (nw, par) != 0) goto ERR;
      geometry_changed= 1;
    }
    else
    if (strcmp (str, "-cmd_button_2") == 0)
    {
      if (_ned_tk_setup_special (nw, NED_TK_CMD_MOUSE_B2, par) != 0) goto ERR;
    }
    else
    if (strcmp (str, "-cmd_menu") == 0)
    {
      if (_ned_tk_setup_special (nw, NED_TK_CMD_MENU, par) != 0) goto ERR;
    }
    else
    if (strcmp (str, "-cmd_wins") == 0)
    {
      if (_ned_tk_setup_special (nw, NED_TK_CMD_WINS, par) != 0) goto ERR;
    }
    else
    {
ERR:
      sprintf (interp->result, "illegal par or val '%s'", str);
      return TCL_ERROR;
    }
  }

  if (TK_CONFIG_ARGV_ONLY && geometry_changed)
  {
    ned_tk_redraw_window (nw, 0, 0, nw->num_x_pixels, nw->num_y_pixels);
  }

  return TCL_OK;
}
