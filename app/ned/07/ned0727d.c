/*
 *  FILE %ned/07/ned0727d.c
 *
 *  copy block
 *
 *  written:       1997-03-31
 *  latest update: 1997-03-31 11:10:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_buffer_copy ()
{
  set_repeat_command (ned_buffer_copy);
  ned_wc_buffer_copy (aw, -1, 0);
  ned_fresh_buffer ();
}
