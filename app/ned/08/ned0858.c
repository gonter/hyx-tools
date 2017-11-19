/*
 *  FILE %ned/08/ned0858.c
 *
 *  see also:
 *  - ned_blk_iconify ()
 *  - ned_rename_object ()
 *  - ned_cb_rename_frame ()
 *
 *  written:       1995-02-09
 *  latest update: 1999-05-14 21:22:09
 *  $Id: ned0858.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_rename_frame (struct WINDOWCTRL *w, const char *fnm, int file_fmt)
{
  struct FRAMECTRL *fc;
  struct CLUSTERCTRL *cc;
  struct LINE *lc_act, *lc_first;       /* pointers from WINDOWCTRL *w      */

  /* Hypertext frames are not only renamed in the window itself, instead,   */
  /* their name must be changed in the text, that is in the frame-tag.      */

printf ("0858: rename_frame: fnm='%s' file_fmt=%d\n", fnm, file_fmt);
  if (w == (struct WINDOWCTRL *) 0
      /* || w->file_type == FTY_FTRWDW */
      || (fc= (struct FRAMECTRL *) w->file_or_frame) == (struct FRAMECTRL *) 0
      || (cc= fc->cluster) == (struct CLUSTERCTRL *) 0
      || fnm == (char *) 0
      || *fnm == 0
     ) return -1;

  /* save pointers of the old window control structure */
  lc_act= w->WC_act;
  lc_first= w->WC_first;

  /* reset pointers in the old window and frame control structures */
  w->WC_act= w->WC_first= (struct LINE *) 0;
  w->file_or_frame= (void *) 0;

  if (fc->links-- == 0)         /* most likely, fc->links will now be 0     */
    ned_deactivate_frame (fc);

  if ((fc= ned_activate_frame (cc, fnm, w, 0x02, file_fmt,
                               (char *) 0, (char *) 0))
      == (struct FRAMECTRL *) 0)
  {
    /* T2D: this is a problem!!! */
  }

  w->f_upd= 1;

  /* if original frame didn't contain any lines, don't bother to            */
  /* insert anything in the newly activated frame                           */
  if (lc_act != (struct LINE *) 0)
  {
    struct LINE *lc_insert;             /* insert position in new window    */
    struct LINE *lc_xx;

    /* 1a. find the end of the new frame,                                   */
    /* 1b. remove last line, containing the end-of-frame tag                */
    /* 2a. find the beginning of the old frame,                             */
    /* 2b. remove first line containing the begin-of-frame tag              */
    /* 3.  append old frame to new frame to produce a complete              */
    /*     frame with begin and end frame tags                              */

    /* 1a. */
    if ((lc_insert= ned_find_last_line (w->WC_act)) != (struct LINE *) 0)
    {
      struct LINE *lc_top;              /* top line of old w                */

      lc_xx= lc_insert;
      if (lc_insert->prev != (struct LINE *) 0)
      { /* 1b. */
        lc_insert= lc_insert->prev;
        lc_xx->prev= (struct LINE *) 0;
        ned_lines_free (lc_xx);
      }

      /* 2a. */
      lc_xx= lc_top= ned_find_first_line (lc_act);
      if (lc_top->next != (struct LINE *) 0)
      { /* 2b. */
        lc_top= lc_top->next;
        lc_xx->next= (struct LINE *) 0;
        ned_lines_free (lc_xx);
      }

      lc_insert->next= lc_top;
      lc_top->prev= lc_insert;
    }

    w->WC_act= w->WC_first= lc_insert;
  }

  return 0;
}
