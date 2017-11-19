/*
 *  FILE %ned/08/ned0803.c
 *
 *  jump to the next feature
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1998-08-16 12:32:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_feature_next ()
{
  struct LINE    *p;
  struct FEATURE *f;
  int x;

  if (aw == (struct WINDOWCTRL *) 0 || aw->WC_act == (struct LINE *) 0)
     goto NF;

  p= aw->WC_act;
  if (p->ftr != (struct FEATURE *) 0)
  {
    x= aw->cx + aw->hv - aw->ax;
    for (f= p->ftr; f != (struct FEATURE *) 0; f= f->ftr_next)
        if (f->ftr_pos > x) goto END;
  }

  for (;;)
  {
    if ((p= p->next) == (struct LINE *) 0) goto NF;
    if (p->ftr != (struct FEATURE *) 0) break;
  }

  aw->WC_act= p;
  f= p->ftr;

END:
  aw->cx= f->ftr_pos - aw->hv + aw->ax;
  ned_w_jmp_aktline (aw, NEDJMP_LINE_MID, 0, NEDJMP_FLAG_REDRAW);
  show_feature (f);
  return;

NF:
  ned_message_1 ("no next feature");
}
