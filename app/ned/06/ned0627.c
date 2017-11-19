/*
 *  FILE %ned/06/ned0627.c
 *
 *  open a file in a window
 *  - never used!!
 *
 *  written:       1993-02-21
 *  latest update: 1996-03-16  1:48:24
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int open_file_and_window (char *filename)
{
  q_jmpwdw (p_wdwopen ());
  q_fnm (filename);
  s_fget (aw);
  ned_display_window (aw);
  take_history_notes (aw);

  return 0;
}
