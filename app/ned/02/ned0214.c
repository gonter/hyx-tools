/*
 *  FILE %ned/02/ned0214.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *                 1991 05 29: Revision
 *  latest update: 1997-10-26 11:11:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int W_TEXT_MAX_X;
extern int W_TEXT_MAX_Y;

static int pr_flag= 0;
static int pr_ax, pr_ay;
static int pr_bx, pr_by;
extern int NED_TEXT_MAX_X, NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
int ned_window_size (
register struct WINDOWCTRL *wc,
int p,                          /* Size Modus                               */
int f)                          /* 1 -> Cursor Position anpassen            */
{
  int aax, aay;
  int w_text_max_x;
  int w_text_max_y;

  if (wc == (struct WINDOWCTRL *) 0) return -1;

  aax= wc->ax;
  aay= wc->ay;

  w_text_max_x= NED_TEXT_MAX_X;
  w_text_max_y= NED_TEXT_MAX_Y;

  if (pr_flag)
  {
    wc->ax= pr_ax; wc->ay= pr_ay;
    wc->bx= pr_bx; wc->by= pr_by;
    pr_flag= 0;
    goto MORE;
  }

  switch (p) /* ax */
  {
    case 0: case 1: case 2:
    case 4: case 7: case 8:
      wc->ax= 1;
      break;
    case 3: case 6: case 9:
      wc->ax= (w_text_max_x/2)+1;
      break;
    case 5:
      wc->ax= 0;
      break;
  }

  switch (p) /* ay */
  {
    case 0: case 4: case 5:
    case 6: case 7: case 8: case 9:
      wc->ay= 3;
      break;
    case 1: case 2: case 3:
      wc->ay= (w_text_max_y/2)+2;
      break;
  }

  switch (p) /* bx */
  {
    case 0: case 2: case 3:
    case 6: case 8: case 9:
      wc->bx= w_text_max_x-2;
      break;
    case 1: case 4: case 7:
      wc->bx= (w_text_max_x/2)-2;
      break;
    case 5:
      wc->bx= w_text_max_x-1;
      break;
  }

  switch (p) /* by */
  {
    case 0: case 1: case 2:
    case 3: case 4: case 6:
      wc->by= w_text_max_y - 2;
      break;
    case 5:
      wc->by= w_text_max_y - 1;
      break;
    case 7: case 8: case 9:
      wc->by= (w_text_max_y/2) - 1;
      break;
  }

MORE:
  if (f)
  {
    wc->cx += wc->ax - aax;
    wc->cy += wc->ay - aay;
    wc->w_upd |= 0x05;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
int ned_window_size_preset (int pax, int pay, int pbx, int pby)
{
  if (pax < 0)
  {
    pr_flag= 0; 
    return 0;
  }

  pr_flag= 1;

  pr_ax= pax;
  pr_ay= pay;
  pr_bx= pbx;
  pr_by= pby;

  return 0;
}
