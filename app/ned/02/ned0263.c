/*
 *  FILE %ned/02/ned0263.c
 *
 *  written:       1997-09-07
 *  latest update: 1997-09-07 12:21:13
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_yank_block (int add_mode)
{
  struct MARKER *mrk_beg, *mrk_end;

  mrk_beg= ned_get_marker (NED_MARKER_BEG, 0);
  mrk_end= ned_get_marker (NED_MARKER_END, 0);

  return ned_yank_marked (mrk_beg, mrk_end, add_mode);
}

/* ------------------------------------------------------------------------ */
int ned_yank_marked (
struct MARKER *mrk_beg,
struct MARKER *mrk_end,
int add_mode)
{
  struct LINE *la, *lb;

  if (mrk_beg == (struct MARKER *) 0
      || mrk_end == (struct MARKER *) 0
      || ned_blk_duplicate (mrk_beg->ptr, mrk_end->ptr, &la, &lb,
                            mrk_beg->offset, mrk_end->offset, block_mode)
           == -1
      || la == (struct LINE *) 0
      || lb == (struct LINE *) 0
     )
     return -1;

  ned_store_line_to_buffer (-1, la, lb, add_mode);

  return 0;
}
