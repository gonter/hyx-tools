/*
 *  FILE %ned/07/ned0727b.c
 *
 *  copy block
 *
 *  written:       1997-01-19
 *  latest update: 1997-01-19 14:08:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_blk_copy_before ()
{
  set_repeat_command (ned_blk_copy_before);
  ned_wc_blk_copy (aw, 1);
}
