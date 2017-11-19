/*
 *  FILE %ned/01/ned0109.c
 *
 *  Hilfsfunktionen, elementare Cursorbewegungen:
 *  Word Left, Word Right
 *
 *  written:       1987 04 08
 *                 1991 01 31: Revision
 *  latest update: 2001-02-11 11:44:50
 *  $Id: ned0109.c,v 1.2 2001/02/12 00:03:22 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_wc_word_lr (struct WINDOWCTRL *wc, int jump_mode)
/* JMPWRD_left_beg      1: left, beginning of word, ignoring punctuation    */
/* JMPWRD_right_beg     2: right, beginning of word, ignoring punctuation   */
/* JMPWRD_right_end     3: right, end of word, ignoring punctuation         */
/* JMPWRD_left_beg_2    4: left, beginning of word                          */
/* JMPWRD_right_beg_2   5: right, beginning of word                         */
/* JMPWRD_right_end_2   6: right, end of word                               */
{
  int ch;
  int off;                      /* Cursorposition in der Zeile              */
  int llng;                     /* Laenge der Zeile                         */
#define ST_start        0
#define ST_stop         3
#define ST_text         1
#define ST_blank        2
#define ST_re_text      4
#define ST_re_blank     5
  int st= 0;                    /* Zustand des Automaten                    */
  register struct LINE *lp;
  int mode1;                    /* general directional mode                 */
  int punctuation= 0;           /* 1 -> dont ignore punctuation             */
  int is_delimiter;             /* 1 -> character is not part of token      */

  if (wc == (struct WINDOWCTRL *) 0
      || (lp= wc->WC_act) == (struct LINE *) 0
     ) return;

  off=  wc->cx - wc->ax + wc->hv;
  llng= lp->lng;

#ifdef USE_TK
  tk_resetcup ();
#endif

  switch (mode1= jump_mode)
  {
    case JMPWRD_left_beg_2:  mode1= JMPWRD_left_beg;  punctuation= 1; break;
    case JMPWRD_right_beg_2: mode1= JMPWRD_right_beg; punctuation= 1; break;
    case JMPWRD_right_end_2: mode1= JMPWRD_right_end; punctuation= 1; break;
  }

  if (mode1 == JMPWRD_left_beg && off > 0) off--;
  if (mode1 == JMPWRD_right_end) off++;

  for (;;)
  {
    if ((mode1 == JMPWRD_left_beg && off == 0)
        || (mode1 == JMPWRD_right_beg && off > llng)
        || (mode1 == JMPWRD_right_end && off >= llng)
       ) break;

    ch= get_txt (lp, off);
    is_delimiter= (ch == 0x20 || ch == 0x09)
                  ? 1
                  : (punctuation)
                    ? 0
                    : in_charset (ch, CHARSET_token)
                      ? 0
                      : 1;

    switch (st)
    {
      case ST_start:
        if (is_delimiter)
          switch (mode1)
          {
            default:
              st= ST_blank;
              break;
            case JMPWRD_right_end:
              st= ST_re_blank;
              break;
          }
        else
          switch (mode1)
          {
            default:
              st= ST_text;
              break;
            case JMPWRD_right_end:
              st= ST_re_text;
              break;
          }
        break;

      case ST_text:
        if (is_delimiter)
          st= (mode1 == JMPWRD_left_beg) ? ST_stop : ST_blank;
        break;

      case ST_blank:
        if (!is_delimiter)
          st= (mode1 == JMPWRD_right_beg) ? ST_stop : ST_text;
        break;

      case ST_re_blank:
        if (!is_delimiter) st= ST_re_text;
        break;

      case ST_re_text:
        if (is_delimiter) st= ST_stop;
        break;
    }

    if (st == ST_stop) break;

    if (mode1 == JMPWRD_left_beg) off--;
    else off++;
  }

  if (mode1 == JMPWRD_left_beg && off) off++;
  if (mode1 == JMPWRD_right_end && off) off--;

  if (off > wc->bx - wc->ax + wc->hv ||
      off <          wc->ax + wc->hv)
  {
    wc->cx= (wc->bx - wc->ax)/2 + wc->ax;
    wc->hv= off - wc->cx + wc->ax;
    if (wc->hv < 0)
    {
      wc->cx += wc->hv;
      wc->hv= 0;
    }

    ned_display_window (wc);
  }
  else wc->cx= off - wc->hv + wc->ax;  
}
