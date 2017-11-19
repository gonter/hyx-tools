/*
 *  FILE %ned/07/ned0711.c
 *
 *  set the block begin marker
 *
 *  written:       1997-01-06
 *  latest update: 1997-01-06 19:16:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;

/* ------------------------------------------------------------------------ */
void vi_yank ()
{
  block_mode= BLOCK_MODE_line;
  p_blkbeg ();
  p_blkend ();
}
