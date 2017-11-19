/*
 *  FILE %ned/08/ned0842b.c
 *
 *  search for a feature record at the current cursor position
 *
 *  returns the address of the pointer (!) where the found
 *  feature record is linked
 *
 *  written:       1996-03-10
 *  latest update: 1996-03-10 13:00:41
 *
 */

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FEATURE **ned_feature_find (struct LINE *lp, int x, int range)
{
  struct FEATURE *f0;
  struct FEATURE **f2;
  struct FEATURE **f2_range= (struct FEATURE **) 0;

  if (lp == (struct LINE *) 0
      || x < 0
     ) return (struct FEATURE **) 0;

  for (f2= &lp->ftr;; f2= &((*f2)->ftr_next) )
  {
    if ((f0= *f2) == (struct FEATURE *) 0 || f0->ftr_pos > x) return f2_range;
    if (f0->ftr_pos == x) return f2;

    if (range == 1 && f0->ftr_pos + f0->ftr_replarray_size - 1 >= x)
      f2_range= f2;
  }

  return f2_range;
}
