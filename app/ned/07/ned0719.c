/*
 *  FILE %ned/07/ned0719.c
 *
 *  set block flags in the current window
 *
 *  written:       1987 04 08
 *  latest update: 1997-09-28 10:35:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int blk;
extern struct MARKER b_beg, b_end;
extern struct MARKER b_first, b_last;
extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_set_block_flags ()
{
  register struct LINE *p;              /* pointer for current line         */
  struct LINE *p_first, *p_last;
  int state= 0;                         /* 0 before first marker            */
                                        /* 1 in block                       */
                                        /* 2 behind the second marker       */

  if (b_first.wptr == (struct WINDOWCTRL *) 0
      || b_first.wptr != b_last.wptr
      || (p_first= b_first.ptr) == (struct LINE *) 0
      || (p_last= b_last.ptr) == (struct LINE *) 0
      || (p= ned_find_first_line (p_first)) == (struct LINE *) 0
     ) return 0;

  blk= 1;

  for (; p != (struct LINE *) 0; p= p->next)
  {
    if (p == p_first || p == p_last)
    {
      p->line_flg |= LINE_BLOCK_INBLOCK | LINE_BLOCK_BEGEND;

      if (p == p_first && p == p_last)
      { /* one line block */
        state= 2;
        ned_copy_markers (&b_beg,
                     (b_first.offset <= b_last.offset) ? &b_first : &b_last);
        ned_copy_markers (&b_end,
                     (b_first.offset >= b_last.offset) ? &b_first : &b_last);
      }
      else
      { /* one marker of a multiline block */
        if (state == 0)
        {
          ned_copy_markers (&b_beg, (p == p_first) ? &b_first : &b_last);
          state= 1;
        }
        else
        {
          ned_copy_markers (&b_end, (p == p_first) ? &b_first : &b_last);
          state= 2;
        }
      }
    }
    else
    {
      if (state == 1)
        p->line_flg |= LINE_BLOCK_INBLOCK;
      else
        p->line_flg &= LINE_BLOCK_CLR;
    }
  }

  return 1;
}
