/*
 *  FILE %ned/08/ned0822.c
 *
 *  Schreibt eine Feature Zeile auf ein File (ohne FTR-Codes)
 *
 *  written:       1991 01 30
 *  latest update: 1996-07-26  3:56:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void wr_ftr_txt (FILE *ff, struct FEATURE *fp, long *position)
{
  register struct TXT *tx;
  register char *cp;
  int ll;                       /* Line Length                              */
  int lsl;                      /* Line Segment Length                      */
  struct LINE *lp;
  long xpos;

  /* Feature Text schreiben */
  if ((lp= (struct LINE *) fp->ftr_text_line) == (struct LINE *) 0
     || (tx= lp->txt) == (struct TXT *) 0) return;

  ll= lp->lng;
  lsl= tx->t_lng;
  cp= tx->t;

  xpos= *position;

  while (ll-- > 0)
  {
    if (lsl == 0)
    {
      if ((tx= tx->next) == (struct TXT *) 0)
      {
        *position= xpos;
        return;
      }
      lsl= tx->t_lng;
      cp= tx->t;
    }
    fputc (*cp++, ff);
    xpos++;
    lsl--;
  }

  *position= xpos;
}
