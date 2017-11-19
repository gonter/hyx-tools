/*
 *  FILE %ned/09/ned0929.c
 *
 *  NED's tk widget stuff
 *
 *  implements the NED widget command
 *  - description
 *
 *  written:       1995-09-25
 *  latest update: 2001-02-11 16:49:49
 *  $Id: ned0929.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include <tk.h>
#include <tcl.h>

#include <syslog.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "edtcl.h"
#include "edtk.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
static char *unknown= "<unknown>";


/* ------------------------------------------------------------------------ */
/* tcl syntax:  <window_path> <method> <pars>*                              */
int ned_tk_widget_cmd (
ClientData clientData,
Tcl_Interp *interp,
int argc,
const char *argv [])
{
  NED_Widget *nw;               /* current widget */
  struct WINDOWCTRL *w;         /* current window */
  struct LINE *lp;
  const char *sub_command;
  char *res2;
  long num;
  long num_res;
  char lval [40];

  if ((nw= (NED_Widget *) clientData) == (NED_Widget *) 0
      || (w= nw->ned_window) == (struct WINDOWCTRL *) 0
     )
    return TCL_ERROR;

  if (argc <= 1
      || (sub_command= argv [1]) == (char *) 0
      || *sub_command == 0
      || abbrev ("path_name", sub_command, 4)
     )
  {
    interp->result= nw->window_path;
    return TCL_OK;
  }

  if (abbrev ("configure", sub_command, 4))
    return ned_tk_configure (nw->interp, nw, argc-2, argv+2,
                             TK_CONFIG_ARGV_ONLY);

  if (strcmp (sub_command, "line") == 0)
  {
    num_res= w->znr;
    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
    {
      ned_jmp_2line_by_nr (w, (int) num, 3);
    }

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "ai") == 0)
  {
    num_res= w->ai;
    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
    {
      w->ai= (int) num;
    }

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "ins") == 0)
  {
    num_res= w->ins_flg;
    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
    {
      w->ins_flg= (int) num;
    }

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "wwc") == 0)
  {
    num_res= w->wwc;
    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
    {
      w->wwc= (int) num;
    }

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "size") == 0
      || strcmp (sub_command, "tlines") == 0
     )
  {
    num_res= (long) w->tlines;
    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "hv") == 0)
  {
    num_res= (long) w->hv;
    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "column") == 0)
  {
    num_res= (long) (aw->cx+aw->hv-aw->ax);
    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "winnum") == 0)
  {
    num_res= (long) w->wc_window_number;
    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "update") == 0)
  {
    num_res= (long) w->f_upd;

    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
      w->f_upd= (int) num;

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "taintlevel") == 0)
  {
    num_res= w->wc_taint_level;

    if (argc > 2
        && (num= get_parameter_value (argv [2])) >= 0
       )
      w->wc_taint_level= (int) num;

    goto NUM_RESULT;
  }

  if (strcmp (sub_command, "format") == 0)
  {
    switch (w->file_format)
    {
      case FMT_BINARY:
        res2= "binary";
        break;
      case FMT_ASCII:
        res2= "ascii";
        break;
      case FMT_SGML:
        res2= "sgml";
        break;
      default:
        res2= unknown;
        break;
    }

STATIC_RESULT:
    Tcl_SetResult (interp, res2, TCL_STATIC);
    return TCL_OK;
  }

  if (strcmp (sub_command, "type") == 0)
  {
    switch (w->file_type)
    {
      case FTY_PLAIN:
        res2= "plain";
        break;
      case FTY_HYPER:
        res2= "hyper";
        break;
      case FTY_FTRWDW:
        res2= "ftrwdw";
        break;
      default:
        res2= unknown;
        break;
    }

    goto STATIC_RESULT;
  }

  if (strcmp (sub_command, "active") == 0)
  {
    aw= w;
    return TCL_OK;
  }

  if (strcmp (sub_command, "file") == 0)
  {
    struct FILECTRL *fc;
    res2= unknown;

    if (w->file_type == FTY_PLAIN
        && (fc= (struct FILECTRL *) w->file_or_frame) != (struct FILECTRL *) 0
       )
    {
      res2= fc->FC_fnm_txt;
    }
    goto VOLATILE_RESULT;
  }

  if (strcmp (sub_command, "frame") == 0)
  {
    struct FRAMECTRL *fc;
    res2= unknown;

    if (w->file_type == FTY_HYPER
        && (fc= (struct FRAMECTRL *) w->file_or_frame) !=(struct FRAMECTRL *) 0
       )
    {
      res2= fc->frame_name;
    }
    goto VOLATILE_RESULT;
  }

  if (strcmp (sub_command, "cluster") == 0)
  {
    struct FRAMECTRL *fc;
    struct CLUSTERCTRL *cc;
    res2= unknown;

    if (w->file_type == FTY_HYPER
        && (fc= (struct FRAMECTRL *) w->file_or_frame)!=(struct FRAMECTRL *) 0
        && (cc= fc->cluster) !=(struct CLUSTERCTRL *) 0
       )
    {
      res2= cc->cluster_name_hyx;
    }
    goto VOLATILE_RESULT;
  }

  if (strcmp (sub_command, "yview") == 0)
  {
    double fraction;
    int lines;
    int factor= 1;
    int units;
    int rc;

/* ned_diag_argv (argc, argv); */
    lines= w->znr;

    if (argc < 3)
    {
 
      num_res= (long) lines;

NUM_RESULT:
      sprintf (lval, "%ld", num_res);
      res2= lval;

VOLATILE_RESULT:
      Tcl_SetResult (interp, res2, TCL_VOLATILE);
      return TCL_OK;
    }

    if (argc == 3)
    {
      units= (int) get_parameter_value (argv [2]);
      goto SCROLL;
    }

    rc= Tk_GetScrollInfo (interp, argc, argv, &fraction, &units);

    switch (rc)
    {
      case TK_SCROLL_MOVETO:
        jmpline_relative (w, fraction);
        return TCL_OK;

      case TK_SCROLL_PAGES:
        factor= (w->by - 3);

      case TK_SCROLL_UNITS:
SCROLL:
        lines += units*factor;
        if (lines < 1) lines= 1;
        ned_jmp_2line_by_nr (w, lines, 3);
        return TCL_OK;

      case TK_SCROLL_ERROR:
        return TCL_ERROR;
    }
  }

  if ((lp= w->WC_act) != (struct LINE *) 0)
  {
    char *cp;

    if (abbrev ("curline", sub_command, 4)
        /* T2D: locate real line by displacement */
        && (cp= ned_line_2_string (lp, 0, lp, 32700,
                  (char *) 0, 0, 0L, 0)) != (char *) 0
       )
    {
      Tcl_SetResult (interp, cp, TCL_DYNAMIC);
      return TCL_OK;
    }
    else if (abbrev ("length", sub_command, 3))
    {
      num_res= (long) lp->lng;
      goto NUM_RESULT;
    }
  }

  return TCL_OK;
}
