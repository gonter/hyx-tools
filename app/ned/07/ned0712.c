/*
 *  FILE %ned/07/ned0712.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 05 16: Revision
 *  latest update: 1997-10-26 10:51:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_blk_mode ()
{
  block_mode--;
  if (block_mode < BLOCK_MODE_standard) block_mode= BLOCK_MODE_box;
  ned_display_window (aw);
  back2ground ();
}
