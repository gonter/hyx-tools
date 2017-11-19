/*
 *  FILE %ned/07/ned0724a.c
 *
 *  isolate a marked block
 *
 *  After calling this function, the block will not be part of the
 *  original window any longer.
 *
 *  Realigns WC_act of all windows, if this is in the block and realigning
 *  is not prohibited.  Realigning must not take place e.g. when blocks
 *  are moved, this wouldn't make sense but could cause strange
 *  effects if it's tried...
 *
 *  written:       1987 04 08
 *  latest update: 1999-05-01 19:33:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_blk_isolate2 (
struct MARKER *m1,
struct MARKER *m2,
int no_realign)                 /* realigning WC_act is prohibithed!!       */
{
  struct WINDOWCTRL *wc;        /* window where block is located            */
  struct LINE *p1, *p2;         /* isolated lines                           */
  int block_orientation;        /* block-to-cursor orientation codes        */
  int rc;

  if (m1 == (struct MARKER *) 0
      || (wc= m1->wptr) == (struct WINDOWCTRL *) 0
      || m2 == (struct MARKER *) 0
      || m2->wptr == (struct WINDOWCTRL *) 0
     ) return 0;

  /* NOTE: 1997-06-11 14:58:20 */
  /* wc should be window pointer from one of the markers, right? */
  wc->f_upd= 1;

  switch (block_orientation= ned_blk_orientation (wc->WC_act))
  {
    case 0x06:                  /* Cursor Position mitten im Block          */
      if (no_realign) return 0;
      /* otherwise proceed */

    case 0x00:                  /* Block in anderem Window                  */
    case 0x05:                  /* Cursor Position vor Block                */
    case 0x0A:                  /* Cursor Position nach Block               */

      ned_marker_rel_cb (m1->ptr, m1);
      ned_marker_rel_cb (m2->ptr, m2);
      rc= ned_blk_isolate (m1->ptr,    m2->ptr,    &p1, &p2,
                           m1->offset, m2->offset, block_mode);
      m1->ptr= p1;
      m2->ptr= p2;
      m1->offset= 0;
      return rc;

    case 0x09:                  /* Beginn und Ende vertauscht               */
    case 0x01: case 0x02:       /* kein Block-Ende   angegeben              */
    case 0x04: case 0x08:       /* kein Block-Beginn angegeben              */
    case 0x03: case 0x07:
    case 0x0B: case 0x0C:
    case 0x0D: case 0x0E:
    case 0x0F:                  /* Kombination nicht moeglich !!!           */
    default:                    /* ungueltige Kombination                   */
      return 0;
  }
  
  return 0;
}
