/*
 *  FILE %ned/02/ned0261.c
 *
 *  written:       1997-08-28
 *  latest update: 1997-08-28  0:18:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int key;
extern int repeat;

/* ------------------------------------------------------------------------ */
void vi_digit ()
{
  if (key == '0' && repeat == 0)
  {
    ned_jmp_boln ();
    return;
  }

  repeat= repeat * 10 + key - '0';
}
