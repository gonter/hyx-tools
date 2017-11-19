/*
 *  FILE %ned/07/ned0724.c
 *
 *  isolate a marked block
 *
 *  After calling this function, the block will not be in the
 *  original window any longer.
 *
 *  Realigns WC_act of all windows, if this is in the block and realigning
 *  is not prohibited.  Realigning must not take place e.g. when blocks
 *  are moved, this wouldn't make sense but could cause strange
 *  effects if it's tried...
 *
 *  written:       1987 04 08
 *  latest update: 1997-09-07  9:34:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_blk_isolate (
struct LINE  *s_start,
struct LINE  *s_stop,
struct LINE **d_start,
struct LINE **d_stop,
int sp1,
int sp2,
int copy_mode)
{
  struct LINE *a;               /* last line before the block               */
  struct LINE *b;               /* first line after the block               */
  int start_is_stop;            /* 1 -> block begin and end in same line    */

  if (s_start == (struct LINE *) 0
      || s_stop == (struct LINE *) 0
      /****** || ned_blk_critical () 1996-05-27 14:09:29 */
      /****** T2D: realign other windows if necessary!   */
     ) return 0;

  start_is_stop= (s_start == s_stop);

  /* extract the block from the window and get line list back again */
  switch (copy_mode)
  {
    default:
    case BLOCK_MODE_standard:
      a= s_start;
      /* note: first split at end marker since both markers */
      /*       can be in the same line and offsets would    */
      /*       have to be re-calculated.                    */
      if (ned_split2 (s_stop, &b, sp2, 0) < 0
          || ned_split2 (a, &s_start, sp1, 0) < 0
         ) return 0;

      /* adjust offsets and also begin marker */
      *d_stop= (start_is_stop) ? s_start : s_stop;
      *d_start= s_start;

      s_start->prev= s_stop->next= (struct LINE *) 0;

      if (a != (struct LINE *) 0) a->next= b;
      if (b != (struct LINE *) 0) b->prev= a;
      ned_join2 (a, b);
      break;

    case BLOCK_MODE_line:
    case BLOCK_MODE_box:
      a= s_start->prev;
      b= s_stop->next;
      s_start->prev= s_stop->next= (struct LINE *) 0;
      if (a != (struct LINE *) 0) a->next= b;
      if (b != (struct LINE *) 0) b->prev= a;
      *d_start= s_start;
      *d_stop= s_stop;
      break;
  }

#ifdef __
      if (block_orientation == 0x06)
      { /* cursor is in the block, re-align active line ! */
        wc->WC_act= a;
        ned_w_jmp_aktline (wc, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
      }
#endif
  ned_blk_realign_if_critical (a);

  return 1;
}
