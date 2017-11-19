/*
 *  FILE %ned/06/ned0618.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *  latest update: 1996-01-06 11:26:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include <gg/window.h>

#ifdef W_MODEL_CURSES
#ifdef W_MODEL_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif
#endif

#include "proto.h"

extern int W_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
void p_exit ()
{
#ifndef USE_TK
  w_selpage (0);
  w_setcup (0, 0, W_TEXT_MAX_Y-1);
/*  _dos_setvect (0x10, old_BBREAK); */
  w_setchar (0, 0, W_TEXT_MAX_Y-1, WV_GELB, ' ');
#ifdef W_MODEL_CURSES
  endwin();
#endif /* W_MODEL_CURSES */
#endif /* !USE_TK */
  exit (0);
}
