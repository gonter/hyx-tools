/*
 *  FILE %ned/07/ned0727e.c
 *
 *  copy block
 *
 *  written:       1997-03-31
 *  latest update: 1997-06-29 18:09:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_buffer_copy_before ()
{
  set_repeat_command (ned_buffer_copy_before);
  ned_wc_buffer_copy (aw, 0, 1);
}
