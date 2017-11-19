/*
 *  FILE %ned/07/ned0716.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-10-26 10:50:55
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level, blk;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_hideblk ()
{
  if (oper_level >= LEV_BLK) return;
  blk= !blk;
  ned_display_window (aw);
}
