/*
 *  FILE %ned/08/ned0838a.c
 *
 *  calculate the size of list of lines
 *
 *  written:       1997-12-05
 *  latest update: 1997-12-05  4:17:20
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
long ned_line_list_size (
struct LINE *la,
int la_idx,
struct LINE *lz,
int lz_idx,
int flags)
{
  long size= 0L;
  int lng;
  struct LINE *lp;

  for (lp= la; lp != (struct LINE *) 0; lp= lp->next)
  {
    lng= lp->lng;                               /* length of analyzed line  */

    if (lp == la) lng -= la_idx;                /* first line in block      */
    if (lp == lz && lz_idx < lng) lng= lz_idx;  /* last line in block       */

    size += (long) lng;
    if (flags & 0x0001) size++;
    if (lp == lz) break;
  }
  size++;

  return size;
}
