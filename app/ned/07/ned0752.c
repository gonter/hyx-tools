/*
 *  FILE %ned/07/ned0752.c
 *
 *  find first line in a list of lines
 *
 *  written:       1995-02-11
 *  latest update: 1998-08-16 14:25:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct LINE *ned_find_last_line (struct LINE *lc)
{
  struct LINE *lx;

  if (lc != (struct LINE *) 0)
    while ((lx= lc->next) != (struct LINE *) 0) lc= lx;

  return lc;
}
