/*
 *  FILE %ned/04/ned0418.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1997-10-26 10:51:55
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern int oper_level;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_unlink ()                /* ^K U:  Unlink linked File                */
{
  if (oper_level >= LEV_LINK) return;
  if (aw->file_or_frame == (void *) 0) return;

  if (aw->file_type == FTY_HYPER)
  {
    if (((struct FRAMECTRL *) aw->file_or_frame)->links <= 1) return;
    ((struct FRAMECTRL *) aw->file_or_frame)->links--;
  }
  else
  {
    if (((struct FILECTRL *) aw->file_or_frame)->FC_links <= 1) return;
    ((struct FILECTRL *) aw->file_or_frame)->FC_links--;
  }

  wdw_rst (aw);
  ned_display_window (aw);
}
