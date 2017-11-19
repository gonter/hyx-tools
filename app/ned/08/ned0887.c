/*
 *  FILE %ned/08/ned0887.c
 *
 *  Shift feature records up and down by one line
 *
 *  This is useful to repair feature files when the text file was
 *  edited with another editor.
 *  T2D, NOTE:
 *  1.  These functions leak memory!  Unused feature lines
 *      are simply dropped and not discarded!
 *  2.  The update flag is not set!
 *
 *  written:       2001-04-01
 *  latest update: 2001-04-01 23:14:51
 *  $Id: ned0887.c,v 1.1 2001/04/01 22:45:37 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_ftr_shift_up ()
{
  struct LINE *lp1, *lp2;
  struct FEATURE *fp1;

  for (lp1= aw->WC_act; lp1 != (struct LINE *) 0; lp1= lp2)
  {
    lp2= lp1->next;
    fp1= (lp2 == (struct LINE *) 0) ? (struct FEATURE *) 0: lp2->ftr;
    lp1->ftr= fp1;
  }

  p_refresh ();
}

/* ------------------------------------------------------------------------ */
void ned_ftr_shift_down ()
{
  struct LINE *lp_start, *lp1, *lp2;
  struct FEATURE *fp1;

  lp_start= aw->WC_act;
  for (lp1= ned_find_last_line (lp_start);
       lp1 != (struct LINE *) 0 && lp1 != lp_start ; lp1= lp2)
  {
    lp2= lp1->prev;
    fp1= (lp2 == (struct LINE *) 0 || lp2 == lp_start)
         ? (struct FEATURE *) 0: lp2->ftr;
    lp1->ftr= fp1;
  }

  p_refresh ();
}
