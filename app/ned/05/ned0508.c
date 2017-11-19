/*
 *  FILE %ned/05/ned0508.c
 *
 *  jump to current line
 *
 *  written:       1987 04 08
 *                 1991 06 01: Revision
 *  latest update: 2001-02-11 11:33:30
 *  $Id: ned0508.c,v 1.3 2001/02/12 00:03:30 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_w_jmp_aktline (
struct WINDOWCTRL *wc,
int offset_mode,
int offset,
int flg)                        /* Bit 0: Window neu aufbauen               */
                                /*     1: cx an den Rand setzen             */
{
  int lin;
  int distance;
  struct LINE *first;
  struct LINE *first_prev;

  if (wc == (struct WINDOWCTRL *) 0) return -1;

  /* Zeilennummer der akt. Zeile ermitteln */
  if (!(flg & NEDJMP_FLAG_NO_CNT))
    wc->znr= ned_cnt_line_2beg (wc->WC_act);

  /* wc->WC_act zeigt schon auf die aktuelle Zeile im File;     */
  /* jetzt muss noch wc->first eingerichtet werden              */
  first= wc->WC_act;         /* NOTE: wc->WC_act can be (struct LINE *) 0! */
  distance= wc->by - wc->ay;

  switch (offset_mode)
  {
    case NEDJMP_LINE_TOP: distance= 0; break;
    case NEDJMP_LINE_MID: distance /= 2; break;
    default:
    case NEDJMP_LINE_3:   distance /= 3; break;
    case NEDJMP_LINE_BOT: break;
  }

  distance += offset;

  lin= 0;
  if (first != (struct LINE *) 0)
    for (; lin < distance; lin++)
    {
      if ((first_prev= first->prev) == (struct LINE *) 0) break;
      else first= first_prev;
    }

  wc->WC_first= first;
  wc->cy= wc->ay + lin;

  if (flg & NEDJMP_FLAG_BOLN)
  {
    vi_wc_jmp_boln (wc);
  }
  else
  {
    if (wc->cx >= wc->bx || wc->cx < wc->ax)
    {
      wc->hv += wc->cx - wc->bx + 1;
      wc->cx= wc->bx - 1;
      if (wc->hv < 0)
      {
        wc->cx += wc->hv;
        wc->hv= 0;
      }
    }
  }

  if (flg & NEDJMP_FLAG_REDRAW)
  {
    wc->w_upd |= 0x04;
    ned_display_window (wc);
  }

  return 1;
}
