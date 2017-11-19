/*
 *  FILE %ned/10/ned1019.c
 *
 *  find a button
 *
 *  written:       1995-12-31
 *  latest update: 2001-02-11 12:45:22
 *  $Id: ned1019.c,v 1.4 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "edhyx.h"

#ifndef USE_TK
#include <gg/maus.h>
#endif /* !USE_TK */

#include <gg/keys.h>
#include "proto.h"

extern int akt_buttons;
extern ned_primitive_function *special_event;

/* ------------------------------------------------------------------------ */
int ned_search_button_bar (int x, int y, int t)
{
  struct BUTTON_DESCRIPTOR *bd;

printf ("ned1019.c: x=%d y=%d t=%d\n", x, y, t);
  if (y != 0) return 0;

#ifndef USE_TK
  if (x >=  0 && x <=  5) { maus_menue (t);     return 1; }
  maus_disable ();
#endif /* !USE_TK */

  if (x >=  8 && x <= 13) { p_window_menu ();   return 1; }
  if (x >= 16 && x <= 22)
  {
#ifdef USE_TK
    special_event= &p_ssave;
#else
    p_ssave ();
#endif /* USE_TK */
    return 1;
  }
  if (x >= 25 && x <= 32) { ned_eval_feature ();return 1; }
  if (x >= 33 && x <= 38) { p_save_reload ();   return 1; }

#ifdef LL_BUTTONS_1
  if ((akt_buttons & LL_prev) && x >= 42 && x <= 49)
  {
    p_logic_link_prev ();
    return 1;
  }

  if ((akt_buttons & LL_up  ) && x >= 52 && x <= 59)
  {
    p_logic_link_up ();
    return 1;
  }

  if (x >= 62 && x <= 69)
  {
    if (akt_buttons & LL_menu) p_logic_link_menu (); else
    if (akt_buttons & LL_more) p_logic_link_more (); else
                               p_link_more ();
    return 1;
  }

  if ((akt_buttons & LL_next) && x >= 72 && x <= 79)
  {
    p_logic_link_next ();
    return 1;
  }
#endif

#ifdef LL_BUTTONS_2
  if ((akt_buttons & LL_view) && x >= 54 && x <= 55)
  {
    p_logic_link_view ();
    return 1;
  }

  if ((akt_buttons & LL_sort) && x >= 57 && x <= 58)
  {
    p_logic_link_sort ();
    return 1;
  }

  if ((akt_buttons & LL_lang) && x >= 60 && x <= 61)
  {
    p_logic_link_lang ();
    return 1;
  }

  if ((akt_buttons & LL_)     && x >= 63 && x <= 64)
  {
    p_link_more ();
    return 1;
  }

  if ((akt_buttons & LL_more) && x >= 66 && x <= 67)
  {
    p_logic_link_more ();
    return 1;
  }

  if ((akt_buttons & LL_menu) && x >= 69 && x <= 70)
  {
    p_logic_link_menu ();
    return 1;
  }

  if ((akt_buttons & LL_prev) && x >= 72 && x <= 73)
  {
    p_logic_link_prev ();
    return 1;
  }

  if ((akt_buttons & LL_up  ) && x >= 75 && x <= 76)
  {
    p_logic_link_up   ();
    return 1;
  }

  if ((akt_buttons & LL_next) && x >= 78 && x <= 79)
  {
    p_logic_link_next ();
    return 1;
  }
#endif

  if ((t & 0x03)
      && (bd= locate_button (x, y)) != (struct BUTTON_DESCRIPTOR *) 0
     )
  {
    p_macro (bd->BD_macro_num);
    return 1;
  }

#ifndef USE_TK
  maus_enable ();
#endif /* !USE_TK */
  return 0;
}
