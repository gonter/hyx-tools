/*
 *  FILE %ned/unix/unix2.c
 *
 *  some screen routines for unix curses and ncurses
 *
 *  written:       1992-12-02
 *  latest update: 1995-10-01
 *  $Id: unix2.c,v 1.4 2002/06/12 18:10:40 gonter Exp $
 *
 */

#include <stdio.h>
#include "ed.h"
/* see also: <gg/window.h> */

#ifdef W_MODEL_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif /* W_MODEL_NCURSES */

#define XSETCUP(x,y) move(y,x)
#define XWritechar addch

extern unsigned long ATTRIBS[];

/* ------------------------------------------------------------------------ */
void curses_blit_line (int page, int ax, int ay, int cnt, char *line)
{
#ifdef W_MODEL_NCURSES
  int last_attr= -1;
  int new_attr;
#endif /* W_MODEL_NCURSES */
  int dispchar;

  XSETCUP (ax, ay);
  /* clrtoeol (); */
  for (; cnt > 0; cnt--)
  {
#ifdef W_MODEL_NCURSES
    new_attr= (line[1] & 0x00FF);
    if (last_attr != new_attr)
    {
      attron(ATTRIBS[new_attr]);
      last_attr= new_attr;
    }
#endif /* W_MODEL_NCURSES */
    dispchar= *line & 0x00FF;
    if (dispchar < 0x20 || dispchar > 0x7E) dispchar= '.';
    XWritechar (dispchar);
    line += 2;
  }
  refresh();
  noecho();
}

/* ------------------------------------------------------------------------ */
int curses_prntcol (int p, int x, int y, int a, char *s)
{
  XSETCUP (x, y);
#ifdef W_MODEL_NCURSES
  attron(ATTRIBS[a]);
#endif /* W_MODEL_NCURSES */
  while (*s)
    XWritechar (*s++);
  refresh();
}

/* ------------------------------------------------------------------------ */
int curses_setnchar (int p, int x, int y, int a, int c, int cnt)
{
  XSETCUP (x, y);
#ifdef W_MODEL_NCURSES
  attron(ATTRIBS[a]);
#endif /* W_MODEL_NCURSES */
  while (cnt-- > 0)
    XWritechar (c);
  refresh();
}

/* ------------------------------------------------------------------------ */
int curses_setchar (int p, int x, int y, int a, int c)
{
  XSETCUP (x, y);
#ifdef W_MODEL_NCURSES
  attron(ATTRIBS[a]);
#endif /* W_MODEL_NCURSES */
  XWritechar (c);
  refresh();
}

/* ------------------------------------------------------------------------ */
int curses_setcup (int p, int x, int y)
{
  XSETCUP (x, y);
  refresh ();
}

/* ------------------------------------------------------------------------ */
int curses_scrblk_up (int ax, int ay, int bx, int by, int attr, int cnt)
{
#ifdef JUNK
  WINDOW *win;
  scrollok (stdscr, TRUE);
  win= derwin (stdscr, by-ay, bx-ax, ay, ax);
  wsetscrreg (win, ay, by);
  wscrl (win, cnt);
  refresh ();
  scrollok (stdscr, FALSE);
  delwin (win);
#endif
  p_refresh ();
}

/* ------------------------------------------------------------------------ */
int curses_scrblk_down (int ax, int ay, int bx, int by, int attr, int cnt)
{
#ifdef JUNK
  WINDOW *win;
  scrollok (stdscr, TRUE);
  win= derwin (stdscr, by-ay, bx-ax, ay, ax);
  wsetscrreg (win, ay, by);
  wscrl (win, -cnt);
  refresh ();
  scrollok (stdscr, FALSE);
  delwin (win);
#endif
  p_refresh ();
}

/* ------------------------------------------------------------------------ */
int curses_scrblk_left ()
{
  p_refresh ();
}

/* ------------------------------------------------------------------------ */
int curses_scrblk_right ()
{
  p_refresh ();
}

/* ------------------------------------------------------------------------ */
void curses_cls ()
{
  /* clear (); */
  erase ();
}

/* ------------------------------------------------------------------------ */
#ifdef W_MODEL_CURSES
void curses_bell ()
{
  beep ();
}
#endif /* W_MODEL_CURSES */

/* ------------------------------------------------------------------------ */
#ifdef W_MODEL_NCURSES
void ncurses_bell ()
{
  beep ();
}
#endif /* W_MODEL_NCURSES */
