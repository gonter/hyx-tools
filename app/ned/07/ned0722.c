/*
 *  FILE %ned/07/ned0722.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *  latest update: 1996-05-27 13:56:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
int ned_blk_orientation (struct LINE *p)
{
  register struct LINE *pp;
  int pos= 0;           /* Bit 0: BEGIN nach p */
                        /*     1: BEGIN vor  p */
                        /*     2: END   nach p */
                        /*     3: END   vor  p */

  for (pp= p; pp != (struct LINE *) 0; pp= pp->next)
  {
    if (pp == b_beg.ptr) pos |= 0x01;
    if (pp == b_end.ptr) pos |= 0x04;
  }

  for (pp= p; pp != (struct LINE *) 0; pp= pp->prev)
  {
    if (pp == b_beg.ptr) pos |= 0x02;
    if (pp == b_end.ptr) pos |= 0x08;
  }

  return pos;
}
