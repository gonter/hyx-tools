/*
 *  FILE %ned/04/ned0412.c
 *
 *  abandon any text in the named window
 *  (former p_2abandon)
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1999-04-25 16:31:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct FILECTRL *files;

/* ------------------------------------------------------------------------ */
void ned_wc_abandon (struct WINDOWCTRL *wc)
{
  if (wc == (struct WINDOWCTRL *) 0) return;

  ned_reset_markers (wc);

  switch (wc->file_type)
  {
    case FTY_PLAIN:
      {
        struct FILECTRL *fc;
        fc= (struct FILECTRL *) wc->file_or_frame;

        if (fc != (struct FILECTRL *) 0)
          if (fc->FC_links > 1)
          {
            fc->FC_links--;
          }
          else
          {
            ned_lines_free (wc->first);
            file_free (fc);
          }
      }
      break;

    case FTY_HYPER:
      {
        struct FRAMECTRL *fc;
        fc= (struct FRAMECTRL *) wc->file_or_frame;

        if (fc != (struct FRAMECTRL *) 0)
        {
          if (fc->links > 1)
          {
            fc->links--;
          }
          else
          {
            /* frame_free (fc); oder so aehnlich!!!! ########## */
            /* ...statt dessen: */
            fc->frame_status= FRAME_is_defined; /* free_frame_control */
            ned_lines_free (wc->first);
          }
        }
      }
      break;

    case FTY_FTRWDW:
      /* ATTN: don't do anything, those lines belong to another window!     */
      /*       just close the control structures of the feature window.     */
      break;
  }

  wdw_rst (wc);
}
