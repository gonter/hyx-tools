/*
 *  FILE %ned/07/ned0733.c
 *
 *  Operationen mit Blocks und Markern
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *                 1991 12 30: revision
 *  latest update: 1997-10-26 10:50:34
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

#define Ret_Err /* -1 */
#define Ret_OK  /*  0 */

/* ------------------------------------------------------------------------ */
void q_jmp_marker (struct MARKER *m)
{
  struct WINDOWCTRL *mw;
  int lnr;

  if (m == (struct MARKER *) 0
      || (mw= m->wptr) == (struct WINDOWCTRL *) 0
     ) return Ret_Err;

  if (aw == mw)
  {
JUMP:
    aw->cx= m->offset - aw->hv + aw->ax;

    /* NOTE: m->ptr can be a pointer to a line which no longer is in the    */
    /*       window so the validity of the line should be verified.         */
    if ((lnr= ned_cnt_line_relative (aw->WC_act, m->ptr)) > 0)
    {
      aw->WC_act= m->ptr;
      aw->znr= lnr;
    }

    ned_w_jmp_aktline (aw, NEDJMP_LINE_3, 0,
                       NEDJMP_FLAG_REDRAW|NEDJMP_FLAG_NO_CNT);
    return Ret_OK;
  }

  if (q2_jmpwdw (mw) == 0)
  {
    q0_jmpwdw (mw);
    goto JUMP;
  }

  return Ret_Err;
}
