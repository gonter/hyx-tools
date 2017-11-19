/*
 *  File %ned/unix/keyboard.c
 *
 *  adaption of keyboard routines for Unix
 *
 *  written:       1993-06-29
 *  latest update: 2001-04-01 23:41:39
 *  $Id: keyboard.c,v 1.3 2005/09/04 18:36:07 gonter Exp $
 *
 */

/*** #define DEBUG_SHOW_KEYS ***/

#include "ed.h"
#include "proto.h"

#ifdef W_MODEL_CURSES
#ifdef W_MODEL_NCURSES
#include <ncurses.h>
#else
#include <curses.h>
#endif /* W_MODEL_NCURSES */
static int saved_key= ERR;
#endif /* W_MODEL_CURSES */

#ifdef USE_TK
#include <tk.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "edtcl.h"
#endif /* USE_TK */

static int key;
extern int MPflag;
extern struct WINDOWCTRL *aw;
extern ned_primitive_function *special_event;

/* ------------------------------------------------------------------------ */
int kbtype ()
{
  return 0;
}
void kbin_set_AT () { }
void kbhit_set_AT () { }

/* ------------------------------------------------------------------------ */
int kbin ()
{
#ifndef USE_TK
  int rc;
#endif /* !USE_TK */

  setcup (aw);
#ifdef USE_TK
  for (key= 0; key == 0; )
  {
    Tk_DoOneEvent (0);
    if (MPflag) return -1;      /* @@ 1996-11-03 12:59:21 */

    /* see %ned/10/ned1019.c ned_search_button_bar () */
    if (special_event != (ned_primitive_function *) 0)
    {
      (*special_event) ();
      special_event= (ned_primitive_function *) 0;
    }
  }
  return key;
#else
  if (saved_key != ERR)
  {
    rc= saved_key;
    saved_key= ERR;
  }
  else while ((rc= getch ()) == ERR);

  return rc;
#endif /* !USE_TK */
}

/* ------------------------------------------------------------------------ */
int kbhit ()
{
#ifndef USE_TK
  setcup (aw);
  if (saved_key != ERR) return 1;
  if ((saved_key= getch ()) != ERR) return 1;
#endif /* !USE_TK */

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef USE_TK
void NED_tk_key_pressed (ClientData clientData, XEvent *eventPtr)
{
  XKeyEvent *ke;
  KeySym keysym;
  XComposeStatus compose;
  char buffer [80];
  char buffer2 [80];
  int tl;
  int shift_state;

  key= 0;

  if (eventPtr == (XEvent *) 0
      || eventPtr->type != KeyPress
      || (ke= (XKeyEvent *) eventPtr) == (XKeyEvent *) 0
     )
    return;

  tl= XLookupString (ke, buffer, 60, &keysym, &compose);
  buffer [tl]= 0;
  shift_state= ke->state;

#ifdef DEBUG_SHOW_KEYS
printf ("shift_state=0x%04X keysym=0x%04X\n", shift_state, keysym); ***/
#endif

  if ((keysym & 0xFF00) == 0xFF00) /* function keys */
  {
    key= keysym & 0x00FF;

    if (key >= 0xE1 && key <= 0xEF)
    { /* EMACS-Keys */
      key= 0;
      return;
      goto DONE;
    }

    if (shift_state & 0x0003) /* Shift or Caps-Lock */
    {
      if (key == 0x0008) {} else
      if (key == 0x0009) key= 0x0001; else
      if (key >= 0x00BE && key <= 0x00C9) key= key + 0x000C; else
      key= 0x0000;
    }
    else
    if (shift_state & 0x0004) /* CTRL */
    {
      if (key == 0x0008) {} else
      if (key == 0x0009) key= 0x0002; else
      if (key == 0x00C9) key= key + 0x0016; else
      if (key >= 0x00BE && key <= 0x00C8) key= key + 0x0018; else
      if (key >= 0x0050 && key <= 0x0057) key= key + 0x0048; else
      key= 0x0000;
    }
    else
    if (shift_state & 0x0018) /* Left-ALT or Right-ALT */
    {
      if (key == 0x0008) {} else
      if (key == 0x0009) key= 0x0003; else
      if (key >= 0x00BE && key <= 0x00C9) key= key + 0x0032; else
      if (key >= 0x0050 && key <= 0x0057) key= key + 0x0051; else
      /* numeric keypad: 0xAA='*'; 0xAF='/'; 0xB0..0xB9=numbers */
      if (key >= 0x00AA && key <= 0x00B9) key= key + 0x0100; else
      key= 0x0000;
    }
    else /* no shift key or anything else */
    {
      /* numeric keypad: 0xAA='*'; 0xAF='/'; 0xB0..0xB9=numbers */
      if (key >= 0x00AA && key <= 0x00B9) { key= key - 0x80; goto DONE; }
    }

    if (key != 0x000D && key != 0x0008 && key != 0x001B)
      key |= 0x0100;
  }
  else
  {
    key= keysym;

    if (shift_state & 0x0004) /* CTRL */
    {
      if (key >= 'a' && key <= 'z') key= key - 0x60; else
      if (key >= 'A' && key <= '^') key= key - 0x40;
    }

    if (shift_state & 0x0018) /* Left-ALT or Right-ALT */
    {
      if (key >= 0x20 && key <= 0x2F) key= key        + 0x014E; else
      if (key >= 0x3A && key <= 0x40) key= key        + 0x011F; else
      if (key >= 0x30 && key <= 0x5F) key= key - 0x10 + 0x0100; else
      if (key == 0x60)                key=              0x0112; else
      if (key >= 0x7B && key <= 0x7E) key= key        + 0x009A; else
      if (key >=  'a' && key <=  'z') key= key - 0x30 + 0x0100; else
      key= 0;
    }
  }

DONE:
  if (key == 0)
  {
    sprintf (buffer2,
             "tl=%d keysym=0x%04uX shift_state=0x%04X keyval=0x%04X '",
             tl, keysym, shift_state, key);
    ned_message_3 (buffer2, buffer, "'");
  }
}
#endif /* USE_TK */
