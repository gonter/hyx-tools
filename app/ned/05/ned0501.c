/*
 *  FILE %ned/05/ned0501.c
 *
 *  switch auto indent toggle
 *
 *  written:       1987 04 08
 *  latest update: 1995-09-26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_aitoggle ()
{
  aw->ai= !aw->ai;
}
