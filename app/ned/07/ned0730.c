/*
 *  FILE %ned/07/ned0730.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1991 05 16: Revision
 *  latest update: 1997-09-07  9:25:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/filename.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_blk_read ()                       /* Read Block from File  */
{
  struct LINE *la, *lb;
  struct WINDOWCTRL dummy;
  char fnm [MAX_FNM_LENGTH];

  if (oper_level >= LEV_FBLK || aw->file_type == FTY_FTRWDW) return;

  fnm [0]= 0;
  if (rd_str ("Read Block: ", fnm, MAX_FNM_LENGTH) == -1) return;

  wdw_rst (&dummy);
  ned_f_read (&dummy, fnm,
          (char *) 0,   /* T2D: specify feature file ?? */
          0, &la, &lb, 0L, 0x7FFFFFFFL);

  if (la == (struct LINE *) 0 || lb == (struct LINE *) 0)
  { /* READ ERROR */
    ned_error_message ("File not found! (ESC)");
    return;
  }

  if (aw->first == (struct LINE *) 0)
  {
    aw->first= aw->WC_act= la;
  }
  else
  {
    struct MARKER *mrk_beg;

    if ((mrk_beg= ned_get_marker (NED_MARKER_BEG, 0)) != (struct MARKER *) 0)
      ned_reset_block_flags (mrk_beg->wptr);

    ned_blk_insert2 (aw->WC_act, aw->cx + aw->hv - aw->ax, la, lb);
  }

  aw->f_upd= 1;
  aw->tlines= ned_cnt_total_lines (aw->WC_act);
  ned_set_marker2 (aw, la, 0, ned_get_marker (NED_MARKER_BEG, 1));
  ned_set_marker2 (aw, lb, lb->lng, ned_get_marker (NED_MARKER_END, 1));
  ned_set_block_flags ();
  ned_blk_screen ();
}
