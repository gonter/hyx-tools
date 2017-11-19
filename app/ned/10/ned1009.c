/*
 *  FILE %ned/10/ned1009.c
 *
 *  Display buttons on the screen
 *  T2D: TK Version, use TK's buttons!
 *
 *  written:       1991-07-03
 *  latest update: 1997-10-26 10:21:44
 *  $Id: ned1009.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"
#include <gg/window.h>

int akt_buttons= 0x000F;
extern int akt_page;
extern int W_TEXT_MAX_X;
extern struct BUTTON_DESCRIPTOR *buttons;

#define BUTTON_COLOR1 (WV_WEISS|W_HELL|WH_VIOLETT)
#define BUTTON_COLOR2 (WV_GELB|WH_VIOLETT)

/* ------------------------------------------------------------------------ */
void show_buttons (struct WINDOWCTRL *wc)
{
  struct BUTTON_DESCRIPTOR *bd;

  akt_buttons= wc->wc_ll_flags;
  w_setnchar (akt_page,  0,  0, WV_SCHWARZ, ' ', 80);

  w_prntcol  (akt_page,  0,  0, BUTTON_COLOR1, " MENU ");
  w_prntcol  (akt_page,  8,  0, BUTTON_COLOR1, " WINS ");
  w_prntcol  (akt_page, 16,  0, BUTTON_COLOR1, " close ");
  w_prntcol  (akt_page, 25,  0, BUTTON_COLOR1, " exec ");
  w_prntcol  (akt_page, 33,  0, BUTTON_COLOR1, " rel. ");

#ifdef LL_BUTTONS_1
  if (akt_buttons & LL_prev)
    w_prntcol  (akt_page, 42,  0, BUTTON_COLOR2, "<<prev<<");
  if (akt_buttons & LL_up)
    w_prntcol  (akt_page, 52,  0, BUTTON_COLOR2, "^^ up ^^");
  if (akt_buttons & LL_more)
    w_prntcol  (akt_page, 62,  0, BUTTON_COLOR2, "* more *"); else
  if (akt_buttons & LL_menu)
    w_prntcol  (akt_page, 62,  0, BUTTON_COLOR2, "v menu v"); else
    w_prntcol  (akt_page, 62,  0, BUTTON_COLOR2, "?? links");
  if (akt_buttons & LL_next)
    w_prntcol  (akt_page, 72,  0, BUTTON_COLOR2, ">>next>>");
#endif

#ifdef LL_BUTTONS_2
  if (akt_buttons & LL_view)
    w_prntcol  (akt_page, 54,  0, BUTTON_COLOR2, "AV");
  if (akt_buttons & LL_sort)
    w_prntcol  (akt_page, 57,  0, BUTTON_COLOR2, "AS");
  if (akt_buttons & LL_lang)
    w_prntcol  (akt_page, 60,  0, BUTTON_COLOR2, "AL");
  if (akt_buttons & LL_)
    w_prntcol  (akt_page, 63,  0, BUTTON_COLOR2, "??");
  if (akt_buttons & LL_more)
    w_prntcol  (akt_page, 66,  0, BUTTON_COLOR2, "**");
  if (akt_buttons & LL_menu)
    w_prntcol  (akt_page, 69,  0, BUTTON_COLOR2, "vv");

  if (akt_buttons & LL_prev)
    w_prntcol  (akt_page, 72,  0, BUTTON_COLOR2, "<<");
  if (akt_buttons & LL_up)
    w_prntcol  (akt_page, 75,  0, BUTTON_COLOR2, "^^");
  if (akt_buttons & LL_next)
    w_prntcol  (akt_page, 78,  0, BUTTON_COLOR2, ">>");
#endif

  for (bd= buttons; bd != (struct BUTTON_DESCRIPTOR *) 0; bd= bd->BD_next)
  {
    /**************************
    if (bd->BD_x == 0 && bd->BD_y >= NED_TEXT_MAX_Y)
      w_setnchar (akt_page, 0, bd->BD_y, 0, ' ', W_TEXT_MAX_X);
    **************************/
    w_prntcol (akt_page, bd->BD_x, bd->BD_y, bd->BD_colour, bd->BD_text);
  }
}
