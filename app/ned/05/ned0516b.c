/*
 *  FILE %ned/05/ned0516b.c
 *
 *  join two lines and link up the results
 *
 *  written:       1995-03-22
 *  latest update: 1996-10-17 10:07:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_join2 (struct LINE *lp1, struct LINE *lp2)
{
  struct LINE *lp3;

  if (lp2 == (struct LINE *) 0) return 0;

  lp3= lp2->next;
  if (ned_join (lp1, lp2) == -1) return -1;
  if ((lp1->next= lp3) != (struct LINE *) 0) lp3->prev= lp1;

  return 0;
}
