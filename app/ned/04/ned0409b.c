/*
 *  FILE %ned/04/ned0409b.c
 *
 *  save the current file after possibly renaming it
 *
 *  This is used to emulate PICO's write out command.
 *
 *  written:       1996-05-27
 *  latest update: 1996-12-29 22:12:38
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void ned_rename_and_save ()
{
  if (oper_level < LEV_FIO)
  {
    ned_rename_object ();
    ned_w_save (aw, 1);
  }
}
