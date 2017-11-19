/*
 *  FILE %ned/08/ned0841.c
 *
 *  Feature Zeile evaluieren
 *
 *  written:       1991 05 23
 *  latest update: 2001-02-11 12:36:45
 *  $Id: ned0841.c,v 1.2 2001/02/12 00:03:33 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_eval_feature ()
{
  struct LINE *lp;

  if (aw == (struct WINDOWCTRL *) 0) return;

  if (aw->file_type == FTY_FTRWDW)
  { /* current window is a feature window                                   */
    /* -> 1. save pointer to current line in the feature records            */
    /*    2. abandon the feature window                                     */
    /*    3. jump to the feature window's main window                       */

    struct WINDOWCTRL *w;

    lp= aw->WC_act;
    w= aw->feature_window;
    ned_wc_abandon (aw);
    ned_close_window ();
    q2_jmpwdw (w);
    /*** q0_jmpwdw (w); it's not necessary to display the window ***/
    ned_reset_a_marker ('1');
  }
  else
  { /* normales Window -> Markup suchen */
    /* ########### gueltiges Markup suchen !!!!!!!!! ########## */
    struct FEATURE **f2;

    ned_set_marker (aw, '1');
    if ((f2= ned_feature_find3 (1)) == (struct FEATURE **) 0
        || (lp= (struct LINE *) (*f2)->ftr_text_line) == (struct LINE *) 0
       )
    { /* no feature here, maybe a markup? (not yet) */

      /* try also to find a word here */
      if (ned_find_bracket (1) == 0
          || q_eval_tag () == 0
          || q_ofile (NED_OPENF_REDRAW | NED_OPENF_CONTEXT
                        | NED_OPENF_HISTORY | NED_OPENF_EXISTS) == 0
         ) return;

      ned_cross_ref ((char *) 0, -1, 0, 0, 1);
      return;
    }
  }

  ned_eval_line (lp, 1, lp, lp->lng-1, 0);
}
