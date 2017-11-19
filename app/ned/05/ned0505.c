/*
 *  FILE %ned/05/ned0505.c
 *
 *  elementare Editierfunktionen: Zeile anspringen und anzeigen
 *
 *  written:       1987 04 08
 *                 1990 05 20: Revision
 *                 1991 06 02: Revision
 *  latest update: 1997-06-28 22:45:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_jmp_2line_by_nr (
register struct WINDOWCTRL *wc,
int lnr,                        /* Zielzeile: Return: 0 -> Fehler;  1 -> OK */
int flg)                        /* Bit 0: Window neu aufbauen               */
                                /*     1: cx an den Rand setzen             */
{
  register struct LINE *lp;

  ned_set_marker (wc, '\'');

  if ((lp= ned_get_line_by_nr (wc->WC_act, &lnr)) != (struct LINE *) 0)
  {
    wc->WC_act= lp;
    wc->znr= lnr;

    ned_w_jmp_aktline (wc, NEDJMP_LINE_MID, 0, flg | NEDJMP_FLAG_NO_CNT);
  }

  return 1;
}
