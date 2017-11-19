/*
 *  FILE %ned/07/ned0738.c
 *
 *  written:       1997-12-05
 *  latest update: 1997-12-05 11:34:08
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int blk;
extern int block_mode;

/* ------------------------------------------------------------------------ */
char *ned_block_2_string (
char *buffer,
int  maxBytes,
long offset,
int flags)
{
  int beg_offset;
  int end_offset;
  struct MARKER *mrk_beg;
  struct MARKER *mrk_end;

  if (blk == 0
      || (mrk_beg= ned_get_marker (NED_MARKER_BEG, 0)) == (struct MARKER *) 0
      || (mrk_end= ned_get_marker (NED_MARKER_END, 0)) == (struct MARKER *) 0
     ) return (char *) 0;

  switch (block_mode)
  {
    case BLOCK_MODE_standard:
    case BLOCK_MODE_box:
      beg_offset= mrk_beg->offset;
      end_offset= mrk_end->offset;
      break;

    case BLOCK_MODE_line:
    default:
      beg_offset= 0;
      end_offset= 32700;  /* @@@ T2D */
      break;
  }

  return ned_line_2_string (
           mrk_beg->ptr, beg_offset,
           mrk_end->ptr, end_offset,
           buffer,
           maxBytes,            /* there is extra space for the 0-char */
           offset,
           flags);
}
