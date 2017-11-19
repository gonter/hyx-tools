/*
 *  FILE %ned/02/ned0248.c
 *
 *  vi emulation: repeat last command
 *  note: doesn't work for all commands!
 *
 *  written:       1994-02-06
 *  latest update: 1996-02-03 17:48:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* static void ((*cdecl last_fnc)()); */
static void ((*last_fnc)(void))= (void *) 0;

/* ------------------------------------------------------------------------ */
void vi_repeat_last_command ()
{
  if (last_fnc != (void *) 0)
    (*last_fnc) ();
}

/* ------------------------------------------------------------------------ */
int set_repeat_command (void (*fnc)(void))
{
  last_fnc= fnc;
  return 0;
}
