/*
 *  FILE %ned/07/ned0727a.c
 *
 *  copy block
 *
 *  written:       1997-01-19
 *  latest update: 1997-03-31 11:01:44
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_blk_copy ()
{
  set_repeat_command (ned_blk_copy);
  ned_wc_blk_copy (aw, 0);
}
