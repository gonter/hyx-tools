/*
 *  FILE %ned/unix/nedelm.c
 *
 *  hack out unresolved symbols for testing purposes
 *  try to do it with elm routines
 *
 *  written:       1994-12-24
 *  latest update: 1996-08-08 20:10:28
 *
 */

/* GG's window library */
#include <stdio.h>
#include "ed.h"

#ifdef W_MODEL_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif /* W_MODEL_NCURSES */

/* ------------------------------------------------------------------------ */
extern int W_TEXT_MAX_X;
extern int W_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
extern WINDOW *stdscr;
extern WINDOW *curscr;
void curses_cls_col (int col)
{
  clearok (curscr,TRUE);
}

/* ------------------------------------------------------------------------ */
void curses_init (int mode)
{
  initscr ();
  W_TEXT_MAX_X= COLS;
  W_TEXT_MAX_Y= LINES;
  leaveok (stdscr, FALSE);
  scrollok (stdscr, FALSE);
#ifdef W_MODEL_NCURSES
  meta (stdscr, TRUE);
  keypad (stdscr, TRUE);
  keypad (stdscr, TRUE);
  notimeout (stdscr, FALSE);
  timeout (1);
#endif
  erase ();
  /* wborder (stdscr, 0,0,0,0,0,0,0,0); */
  raw ();
  noecho ();
#ifdef W_MODEL_NCURSES
  start_color ();
  init_attribs ();
#endif
  refresh ();
}

/* ------------------------------------------------------------------------ */
/* window change signal received */
void curses_sig_winch (void)
{
#ifdef W_MODEL_NCURSES
  _nc_update_screensize ();  /* T2D: this is an ncurses internal function */
#endif /* W_MODEL_NCURSES */
  W_TEXT_MAX_X= COLS;
  W_TEXT_MAX_Y= LINES;
}

/* ------------------------------------------------------------------------ */
#ifdef W_MODEL_NCURSES
unsigned long ncurses_colors [8]=
{
  COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
  COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE
} ;

unsigned long ATTRIBS [256];

/* ------------------------------------------------------------------------ */
int init_attribs ()
{
  int background;
  int foreground;
  int blink;
  int bold;
  int anum;
  int pair;
  
  for (blink= 0; blink<2; blink++)
  for (background= 0; background < 8; background++)
  {
    for (bold= 0; bold < 2; bold++)
    {
      for (foreground= 0; foreground < 8; foreground++)
      {
        anum= ((blink*8)+background)*16+(bold*8)+foreground;
        pair= background*8+foreground;
        init_pair (pair, ncurses_colors [foreground],
                   ncurses_colors [background]);
        ATTRIBS [anum]= COLOR_PAIR (pair)
                        | ((bold == 1) ? A_BOLD : 0)
                        | ((blink == 1) ? A_BLINK : 0);
      }
    }
  }

  return 0;
}
#endif /* W_MODEL_NCURSES */
