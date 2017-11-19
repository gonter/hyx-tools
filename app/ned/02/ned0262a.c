/*
 *  FILE %ned/02/ned0262.c
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

extern int repeat;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void vi_jmp_2line ()
{
  if (repeat) ned_jmp_2line_by_nr (aw, repeat, 0x03);
  else pq_dn ();
}
