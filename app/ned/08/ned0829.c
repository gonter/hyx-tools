/*
 *  FILE %ned/08/ned0829.c
 *
 *  insert a feature record into a feature list
 *
 *  written:       1996-07-25
 *  latest update: 1996-07-25 21:23:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_insert_feature (
struct FEATURE **fp,            /* feature list                             */
struct FEATURE *f)              /* feature entry to be inserted             */
{
  int insert_position= 0;
  struct FEATURE *f2;
  int ftr_pos;

  ftr_pos= f->ftr_pos;

  for (;; fp= &f2->ftr_next)
  {
    if ((f2= *fp) == (struct FEATURE *) 0 || f2->ftr_pos > ftr_pos)
    {
      f->ftr_next= f2;
      *fp= f;
      break;
    }

    insert_position++;
  }

  return insert_position;
}
