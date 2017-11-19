/*
 *  FILE %ned/02/ned0211b.c
 *
 *  close a window
 *
 *  written:       1996-05-26 extracted from ned0211.c
 *  latest update: 1999-04-25 16:29:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int ned_w_close_window (register struct WINDOWCTRL *wc)
{
  register struct FILECTRL *fc;

  if (wc == (struct WINDOWCTRL *) 0) return -1;

  if ((struct FILECTRL *) wc->file_or_frame != (struct FILECTRL *) 0
      && ((struct FILECTRL *) wc->file_or_frame)->FC_links <= 1
      && !(wc->WC_edit_mode & EDIT_NOTOGGLE) /* ??? */
     )
    return -1;  /* can't close window */

  ned_reset_markers (wc);  /* reset markers which are in the current window */

#ifdef USE_TK
  ned_tk_delete_association (wc);
#endif

#ifdef WINSTACK
  if (windows == wc)
  {
    if (wc->WC_next == (struct WINDOWCTRL *) 0) return -1;
    windows= wc->WC_next;
  }

  winstack_delete (wc);
#else
  if (windows == wc)    /* window is the first in line */
  {
    if (wc->WC_next == (struct WINDOWCTRL *) 0)
      return -1;         /* zu loeschendes Window ist das einzige */
    windows= wc->WC_next;
  }
#endif

  if (wc->file_type == FTY_PLAIN
      && (fc=((struct FILECTRL *) wc->file_or_frame)) != (struct FILECTRL *) 0
     )
    fc->FC_links--;

  if (wc->WC_prev != (struct WINDOWCTRL *) 0)
    wc->WC_prev->WC_next= wc->WC_next;
  if (wc->WC_next != (struct WINDOWCTRL *) 0)
    wc->WC_next->WC_prev= wc->WC_prev;

  free_or_what (wc->WC_title_short);
  free_or_what (wc->WC_title_long);
  free (wc);

  return 0;
}
