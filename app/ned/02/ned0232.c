/*
 *  FILE %ned/02/ned0232.c
 *
 *  switch number of line mode
 *
 *  NOTE: Die Umschaltung des Line Modes funktioniert nicht richtig, wenn
 *        die Zeileneinstellung bie Aufruf von NED anders als standardmaessig
 *        eingestellt war und keine Umschaltung des Zeilenmodes waehrend
 *        des NED Laufs vorgenommen wurde.
 *  Grund: Der Zeilenmode kann zu diesem Zeitpunkt nicht ermittelt werden.
 *  Workaround: Es werden verschieden Zeilenmodi durchprobiert, bis
 *              ein brauchbarer gefunden wird.
 *
 *  written:       1991 05 30
 *                 1992 01 01: memorize and restore window and line mode
 *  latest update: 1996-10-29 20:10:23
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int W_TEXT_MAX_Y;

static int line_mode= 0;
static int act_window_mode= -1;
static int w_text_max_y= -1;

/* ------------------------------------------------------------------------ */
void p_switch_line_mode ()
{
  if (++line_mode > 5) line_mode = 1;
  w_set_screen_mode (line_mode);
}

/* ------------------------------------------------------------------------ */
void restore_window_mode ()
{
  if (act_window_mode < 0) return;

  if (w_get_mode () != act_window_mode)
    w_init_mode (act_window_mode, 0x0001);

  if (line_mode)
  {
    w_set_screen_mode (line_mode);
  }
  else
  if (w_text_max_y > 0)
  {
    for (line_mode= 1; line_mode <= 5; line_mode++)
    {
      w_set_screen_mode (line_mode);
      if (W_TEXT_MAX_Y >= w_text_max_y) break;
    }
  }
}

/* ------------------------------------------------------------------------ */
void memorize_window_mode ()
{
  act_window_mode= w_get_mode ();
  w_text_max_y= W_TEXT_MAX_Y;
}
