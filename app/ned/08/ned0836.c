/*
 *  FILE %ned/08/ned0836.c
 *
 *  Evaluierung eines hyx.l Tags
 *  see hyx link evaluation for a description of this function
 *
 *  NOTE: this function can be called when aw == NULL!
 *
 *  written:       1991 05 23
 *                 1992-02-25: access to gopher servers
 *                 1993-01-18: dorothy object access method
 *                 1993-01-31: removed dorothy and installed IOA
 *                             (indirect object access) instead
 *  latest update: 2001-02-11 12:25:13
 *  $Id: ned0836.c,v 1.4 2001/02/12 00:03:33 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/hyx.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern int akt_buttons;
extern struct WINDOWCTRL *aw;
extern int GHYOPT_close_on_logic_link;
extern char *default_template_frame;
extern char *default_start_frame;

#define P1_SIZ 4096
#define LOCATION_SIZ 4096

static int recursion_counter= 0;
static char *YES= "yes";
static char *NO= "no";

/* ------------------------------------------------------------------------ */
int ned_eval_hlink (char *str, int option)
{
  struct CLUSTERCTRL *cl= (struct CLUSTERCTRL *) 0;
  struct WINDOWCTRL *wc;
  int w;
  char *idx_file;               /* position of file attribute               */
  char *idx_fr;                 /* position of frame attribute              */
  char *idx_cl;                 /* position of cluster attribute            */
  char *idx;                    /* position of other attributes             */
  int rc= 0;                    /* return code passed back to caller        */
#ifdef NED_READ_ONLY
  int activation_mode= 0x00;
#else
  int activation_mode= 0x02;
#endif /* !NED_READ_ONLY */
  char *p1= (char *) 0;
  int close_actual_window= 0;
  int save_reload_actual_window= 0;
  int reload_target= 0;
  int f_fmt= -1;
  int flg_wd_setup= 0;
  int flg_open_frame= 0;        /* 1 -> link to some frame                  */
  int flg_clone= 0;             /* clone the frame or file                  */
#ifdef USE_GOPHER
  int goph_f= 0;
#endif

ned_message_2 ("eval_hlink: ", str);

  if ((p1= malloc (P1_SIZ)) == (char *) 0) return -1;

  if (find_attr_value (str, p1, P1_SIZ, "tcl") != -1) mac_call_tcl (p1);
#ifdef USE_TK
  if (find_attr_value (str, p1, P1_SIZ, "tk") != -1) mac_call_tcl (p1);
#endif

  if ((idx= find_attr_name (str, "pgm")) != (char *) 0)
  {
    if (get_attr_value (idx, p1, P1_SIZ, 0x01) == -1) goto ERROR;
    q_shell (p1);
  }

  if (aw != (struct WINDOWCTRL *) 0
      && (idx= find_attr_name (str, "prc")) != (char *) 0
     )
  { /* process the current window somehow */
    if (aw->f_upd) ned_w_save (aw, 1);

    if (get_attr_value (idx, p1, P1_SIZ, 0x01) == -1) goto ERROR;
    q_shell (p1);
    ned_save_reload (aw, WCTDM_no_change);
  }

  if (find_attr_value (str, p1, P1_SIZ, "lookup") != -1)
  {
    if (recursion_counter++ < 10)
      rc= ned_eval_lookup_feature (p1, 0);
    recursion_counter--;
    goto RETURN_0;
  }

  /* logic link -> close actual window (if wished) */
  if (option == HYOPT_logic_link
      && GHYOPT_close_on_logic_link) close_actual_window= 1;

  /* SGML tag attribute: close=yes, close=no, close=condition */
  if (find_attr_value (str, p1, P1_SIZ, "close") != -1)
  {
    if (strcmp (p1, YES) == 0) close_actual_window= 1; else
    if (strcmp (p1, NO)  == 0) close_actual_window= 0;
    /* other conditions: currently not defined */
  }

  if (find_attr_value (str, p1, P1_SIZ, "save") != -1)
  {
    if (strcmp (p1, YES) == 0) save_reload_actual_window= 1; else
    if (strcmp (p1, NO)  == 0) save_reload_actual_window= 0;
    /* other conditions: currently not defined */
  }

  if (find_attr_value (str, p1, P1_SIZ, "reload_target") != -1)
  {
    if (strcmp (p1, YES) == 0) reload_target= 1; else
    if (strcmp (p1, NO)  == 0) reload_target= 0;
    /* other conditions: currently not defined */
  }

#ifndef NED_READ_ONLY
  if (find_attr_value (str, p1, P1_SIZ, "clone") != -1
     && strcmp (p1, YES) == 0) flg_clone= 1;
#endif /* !NED_READ_ONLY */

#ifdef USE_GOPHER
  if ((idx_file= find_attr_name (str, "gh")) != (char *) 0)
  {
    goph_f= 1;
    if (access_gopher (str, p1) == 0) goto GOPHER_FILE;
  }
#endif

  if (find_attr_value (str, p1, P1_SIZ, "prompt") != -1) do_prompt (p1);

  if (find_attr_value (str, p1, P1_SIZ, "fmt") != -1)
  {
    if (strcmp_c (p1, "hyx")  == 0
        || strcmp_c (p1, "sgml") == 0
       ) f_fmt= FMT_SGML;
  }

  if (save_reload_actual_window) ned_save_reload (aw, WCTDM_no_change);

  if ((idx_file= find_attr_name (str, "file")) != (char *) 0
      || (idx_file= find_attr_name (str, "href")) != (char *) 0
     )
  { /* Link auf ein File */
    char *real_fnm= (char *) 0;
    char *virtual_fnm= (char *) 0;

    if (get_attr_value (idx_file, p1, P1_SIZ, 0x01) == -1) goto ERROR;
#ifdef USE_GOPHER
GOPHER_FILE:
#endif

    if ((w= find_file (p1, ned_get_file_path (aw),
                        &real_fnm, &virtual_fnm)) != -1)
    { /* file already loaded */
      q_jmpwdw (w);                     /* NOTE: sets aw= w     */
      if (reload_target) p_fget ();     /* NOTE: operates on aw */
    }
    else
    { /* file not loaded yet */
      if (aw == (struct WINDOWCTRL *) 0) goto MK_NEW_WINDOW;
      if (close_actual_window)
      {
        if (aw->f_upd) ned_w_save (aw, 1);
        ned_wc_abandon (aw);
      }
      else
      {
        ned_window_size_preset (aw->ax, aw->ay, aw->bx, aw->by);
MK_NEW_WINDOW:
        q_jmpwdw (p_wdwopen ());
      }

      q_fnm (real_fnm); /* real_fnm statt p1, 1995-10-31 */
#ifdef USE_GOPHER
      if (goph_f) aw->file_format= FMT_SGML;
#endif
      if (f_fmt != -1) aw->file_format= f_fmt;
      s_fget (aw);
      take_history_notes (aw);
      flg_wd_setup= 1;
    }

    free_or_what (real_fnm);
    free_or_what (virtual_fnm);

    if (eval_window_parameters (aw, str) > 0) flg_wd_setup= 1;
    if (flg_wd_setup) ned_display_window (aw);
    show_buttons (aw);

    goto RETURN_0;
  }

  idx_fr= find_attr_name (str, "fr");
  idx_cl= find_attr_name (str, "cl");
  if (idx_fr != (char *) 0 || idx_cl != (char *) 0) flg_open_frame= 1;

  if (idx_cl != (char *) 0)
  { /* Cluster Angabe im Link */
    if (get_attr_value (idx_cl, p1, P1_SIZ, 0x01) == -1
        || (cl= ned_activate_cluster (p1)) == (struct CLUSTERCTRL *) 0
       )
      goto ERROR;
  }
  else
  { /* Frame im aktuellen Cluster */
    if (!(aw != (struct WINDOWCTRL *) 0
          && aw->file_type == FTY_HYPER
          && aw->file_or_frame != (void *) 0
          && (cl= ((struct FRAMECTRL *) aw->file_or_frame)->cluster)
                  != (struct CLUSTERCTRL *) 0
         )
       )
    {
      cl= ned_get_cluster_list ();
#ifdef NED_READ_ONLY
      activation_mode= 0x01;
#else
      activation_mode= 0x03;
#endif /* !NED_READ_ONLY */
    }
  }

  if (idx_fr != (char *) 0)
  {
    if (get_attr_value (idx_fr, p1, P1_SIZ, 0x01) == -1) goto ERROR;
  }
  else
  {
    if (idx_cl != (char *) 0) strcpy (p1, default_start_frame);
  }

  if (!flg_open_frame && idx_file == (char *) 0) close_actual_window= 0;
  /* a menu within a file?  no problem, just don't close the window */

  wc= (struct WINDOWCTRL *) 0;
  if (aw != (struct WINDOWCTRL *) 0)
  {
    if (close_actual_window)
    {
      if (aw->f_upd) ned_w_save (aw, 1);
      ned_wc_abandon (aw);
      if (flg_open_frame) wc= aw;
      else ned_close_window ();
    }
    else
    {
      ned_window_size_preset (aw->ax, aw->ay, aw->bx, aw->by);
    }
  }

  if (flg_open_frame)
  {
    if (ned_activate_frame (cl, p1, wc, activation_mode, FMT_SGML,
                            default_template_frame, (char *) 0)
       == (struct FRAMECTRL *) 0) goto ERROR;
  }

#ifndef NED_READ_ONLY
  if (flg_clone) ned_rename_object ();
#endif /* !NED_READ_ONLY */

  if (eval_window_parameters (aw, str) > 0)
    ned_display_window (aw);

RETURN_0:
  free (p1);
  return rc;

ERROR:
  free (p1);

  return -1;
}
