/*
 *  FILE %ned/04/ned0405.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1990 01 12: Isolation
 *                 1991 02 03: Revision
 *                 1991 05 31: Revision
 *  latest update: 1997-01-08 10:34:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int q_allsave (int flg)
/* RETURN:                                      */
/* -1: at least one window had an error         */
/*  0: at least one window could not be saved   */
/*  1: all files were saved ok                  */
{
  struct WINDOWCTRL *w;
  int done= 1;

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
    if (w->file_or_frame != (void *) 0)
    {
      if (w->file_type == FTY_HYPER)
           ((struct FRAMECTRL *) w->file_or_frame)->upd= 1;
      else ((struct FILECTRL  *) w->file_or_frame)->FC_upd= 1;
    }

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
    if (w->file_or_frame == (void *) 0
        && w->WC_first != (struct LINE *) 0) done= 0;
    else
    {
      if ((w->file_type == FTY_PLAIN
           && ((struct FILECTRL  *) w->file_or_frame)->FC_upd)
          ||(w->file_type == FTY_HYPER
             && ((struct FRAMECTRL *) w->file_or_frame)->upd))
      { /* save linked files only once */
        if (ned_w_save (w, flg) != 0) done= -1;
      }
    }

  return done;
}
