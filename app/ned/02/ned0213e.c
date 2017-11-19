/*
 *  FILE %ned/02/ned0213e.c
 *
 *  screen control
 *  -  rearange the windows in a stacked mode
 *
 *  written:       1987 04 08
 *  latest update: 1997-10-26 11:10:21
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

#define H_OFFSET 5

extern struct WINDOWCTRL *aw, *windows;
extern int NED_TEXT_MAX_X, NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void p_wdwfaecher ()
{
  int ccx, ccy;
  int aax, aay;
  int w_text_max_x;
  int w_text_max_y;
  int w_cnt= 1;                 /* number of windows    */
  int w_num;                    /* current window       */

  struct WINDOWCTRL *wc;

  w_text_max_x= NED_TEXT_MAX_X;
  w_text_max_y= NED_TEXT_MAX_Y;

  for (wc= windows;
       wc->WC_next != (struct WINDOWCTRL *) 0;
       wc= wc->WC_next) w_cnt++;

  if (w_cnt <= 1 || w_cnt >= 10) goto DONE;

  for (w_num= w_cnt-1;
       wc != (struct WINDOWCTRL *) 0;
       wc= wc->WC_prev, w_num--)
  {
    ccx= wc->cx;  ccy= wc->cy;
    aax= wc->ax;  aay= wc->ay;

    wc->ax= 1 + H_OFFSET*w_num;
    wc->bx= w_text_max_x + 3 - H_OFFSET*(w_cnt - w_num);
    wc->ay= 2 + w_cnt - w_num;
    wc->by= w_text_max_y - 2 - w_num;

    wc->cx += wc->ax - aax;
    wc->cy += wc->ay - aay;
    wc->w_upd |= 0x05;

    ned_w_jmp_aktline (wc, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
  }

DONE:
  aw->w_upd |= 0x05;
  ned_display_window (aw);
}
