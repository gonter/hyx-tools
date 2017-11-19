/*
 *  FILE %ned/10/ned1015.c
 *
 *  exectue item from the mouse menu
 *
 *  written:       1992 07 12
 *  latest update: 1995-08-22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int execute_mm_item (long fc)
{
  struct mm_item *mi;
  ned_primitive *np;

  if (fc == -1L || fc == 0L) return -1;

  /* NOTE: in the old days, fc was really the address of a                  */
  /*       NED primitive function which was casted and called like this:    */
  /*       (*(int (*) ()) fc) ();                                           */
  /*       things have changed ...                                          */

  mi= (struct mm_item *) fc;
  switch (mi->MMI_type)
  {
    case MMI_func:
      /* (*(int (*) ()) mi->MMI_value) (); */
      np= (ned_primitive *) mi->MMI_value;
      (*np) ();
      break;
    case MMI_macro:
      p_macro ((int) mi->MMI_value);
      break;
    default:
      return -1;
  }

  return 0;
}
