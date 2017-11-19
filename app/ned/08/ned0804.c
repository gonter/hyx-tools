/*
 *  FILE %ned/08/ned0804.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1998-08-16 12:32:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_feature_prev ()
{
  struct LINE *p;
  struct FEATURE *f;
  int x;
  int xx= -1;

  if (aw == (struct WINDOWCTRL *) 0 || aw->WC_act == (struct LINE *) 0)
    goto NF;

  p= aw->WC_act;
  if (p->ftr != (struct FEATURE *) 0)
  {
    x= aw->cx + aw->hv - aw->ax;
    for (f= p->ftr; f != (struct FEATURE *) 0; f= f->ftr_next)
        if (f->ftr_pos < x)
           xx= f->ftr_pos - aw->hv + aw->ax;

    if (xx != -1)
    {
      aw->cx= xx;
      goto END;
    }
  }

  for (;;)
  {
    if ((p= p->prev) == (struct LINE *) 0) goto NF;
    if (p->ftr != (struct FEATURE *) 0) break;
  }

  /* hinterstes Feature suchen */
  for (f= p->ftr; f->ftr_next != (struct FEATURE *) 0; f= f->ftr_next);

  aw->WC_act= p;
  aw->cx= f->ftr_pos - aw->hv + aw->ax;
END:
  ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);
  show_feature (f);
  return;

NF:
  ned_message_1 ("no previous feature");
}
