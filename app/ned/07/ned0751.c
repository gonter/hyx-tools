/*
 *  FILE %ned/07/ned0751.c
 *
 *  find first line in a list of lines
 *
 *  written:       1995-02-11
 *  latest update: 1998-08-16 14:26:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct LINE *ned_find_first_line (register struct LINE *lc)
{
  struct LINE *lp;

  if (lc != (struct LINE *) 0)
    while ((lp= lc->prev) != (struct LINE *) 0) lc= lp;

  return lc;
}
