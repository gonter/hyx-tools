/*
 *  FILE %ned/07/ned0703.c
 *
 *  set a marker at two opposing brackets
 *
 *  written:       1996-12-29
 *  latest update: 1997-08-28 11:28:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_group_set_marker ()
{
  ned_set_marker (aw, '(');
  ned_find_bracket (1);
  ned_cursor_right ();
  ned_set_marker (aw, '}');
}
