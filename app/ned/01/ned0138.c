/*
 *  FILE %ned/01/ned0138.c
 *
 *  Speicherverwaltung
 *
 *  written:       1987 04 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:29:29
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
void ned_lines_free (register struct LINE *lp)  /* Eine Liste von Zeilen    */
                                                /* freigeben                */
{
  struct LINE *lp2;

  if ((lp= ned_find_first_line (lp)) == (struct LINE *) 0) return;

  while ((lp2= lp) != (struct LINE *) 0)
  {
    /* 'Anhaengsel' einer Zeile freigeben  */
    tx_free (lp->txt);          /* Text Segmente der Zeile freigeben */

    ned_line_trigger_delete (lp, 1, 0);
    ned_feature_free (lp->ftr);

    lp= lp->next;
    free (lp2);
  }
}
