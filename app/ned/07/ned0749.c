/*
 *  FILE %ned/07/ned0749.c
 *
 *  iconify a block
 *  - see also:
 *    - ned_rename_frame ()
 *    - ned_blk_move ()
 *    - struct MARKER
 *
 *  written:       1993-10-03
 *  latest update: 1998-08-15 12:29:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/filename.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
extern int oper_level;
extern int block_mode;
extern int blk;
extern struct MARKER b_beg, b_end;
extern struct WINDOWCTRL *aw;

static char fnm [MAX_FNM_LENGTH]= "$$clip";

/* ------------------------------------------------------------------------ */
void ned_blk_iconify ()
{
  struct FRAMECTRL *fc_new;
  struct CLUSTERCTRL *cc;
  struct WINDOWCTRL *wc;
  struct WINDOWCTRL *w_source;
  int search_mode= 0x02;
  struct LINE *l_bot;

  if (oper_level >= LEV_BLK
      || (w_source= b_beg.wptr) == (struct WINDOWCTRL *) 0
      || (w_source->WC_edit_mode & EDIT_READ_ONLY)
      || ned_blk_invalid ()     /* T2D: b_beg and b_end checked therein     */
      || rd_str ("destination frame: ", fnm, MAX_FNM_LENGTH) == -1
      || ned_blk_isolate2 (&b_beg, &b_end, 0) == 0
     ) return;

  w_source->f_upd= 1;
  w_source->tlines= ned_cnt_total_lines (w_source->WC_act);
  ned_w_jmp_aktline (w_source, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);

  if (w_source->file_type != FTY_HYPER
      || (fc_new= (struct FRAMECTRL *) w_source->file_or_frame)
          == (struct FRAMECTRL *) 0
      || (cc= fc_new->cluster) == (struct CLUSTERCTRL *) 0
     ) cc= ned_activate_cluster ("%cl0");

  if (cc == (struct CLUSTERCTRL *) 0
      || (fc_new= ned_activate_frame (cc, fnm, (struct WINDOWCTRL *) 0,
                                      search_mode, FMT_SGML,
                                      (char *) 0, (char *) 0))
          == (struct FRAMECTRL *) 0
      || (wc= aw) == (struct WINDOWCTRL *) 0
     )
    return;

  l_bot= ned_find_last_line (wc->WC_act);
  if (block_mode == BLOCK_MODE_line
     && l_bot != (struct LINE *) 0
     && l_bot->prev != (struct LINE *) 0) l_bot= l_bot->prev;

  if ((wc->WC_act= l_bot) == (struct LINE *) 0)
    wc->WC_act= wc->WC_first= b_beg.ptr;
  else 
    ned_blk_insert2 (wc->WC_act, wdw_off(wc), b_beg.ptr, b_end.ptr);

  wc->f_upd= 1;
  wc->tlines= ned_cnt_total_lines (wc->WC_act);

  blk= 1;
  ned_w_jmp_aktline (wc, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);

  ned_memorize_location ();
}
