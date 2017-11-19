/*
 *  FILE %ned/01/ned0138b.c
 *
 *  Speicherverwaltung
 *
 *  written:       1996-07-27
 *  latest update: 1999-04-25 16:29:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_feature_free (register struct FEATURE *f)
{
  struct FEATURE *f2;
  struct LINE *lp;

  while (f != (struct FEATURE *) 0)
  {
    f2= f;
    f= f->ftr_next;

    if ((lp= (struct LINE *) f2->ftr_text_line) != (struct LINE *) 0)
    {
      tx_free (lp->txt);

      ned_line_trigger_delete (lp, 1, 1);
      /* Note: is it possible, that feature lines       */
      /*       have registered callbacks?               */

      free (lp);
    }
    free (f2);
  }
}
