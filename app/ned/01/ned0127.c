/*
 *  FILE %ned/01/ned0127.c
 *
 *  isolate a word at the current cursor postition
 *
 *  written:       1994-04-10: isolated from ned0126.c q_isolate_word()
 *  latest update: 1997-01-15 14:12:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int qq_isolate_word (
char *wp,
int max_lng,
int charset,
struct LINE *lp,
int off,                        /* Cursorposition in der Zeile              */
int llng,                       /* Laenge der Zeile                         */
int go_left)                    /* 1 -> search for the beginning of the word*/
{
  int ch;
  int st= 0;                    /* Zustand des Automaten                    */
  int wl= 0;                    /* length of isolated word                  */

  for (;;)
  {
    if (off < 0 || off >= llng) goto DONE;
    ch= get_txt (lp, off);

    switch (st)
    {
      case 0: /* check the opening character class */
        if (!in_charset (ch, charset)) return 0;
        if (go_left) st= 1;
        else { st= 2; goto ST2; }

      case 1: /* find the beginning of the word */
        if (!in_charset (ch, charset))
        {
          off++;
          st= 2;
          break;
        }
        if (off>0)
        {
          off--;
          break;
        }
        st= 2;

      case 2: /* copy the current word to the buffer */
ST2:
        if (!in_charset (ch, charset) || max_lng <= 1) goto DONE;
        *wp++= (char) ch;
        *wp= 0;
        wl++;
        off++;
        max_lng--;
        break;
    }
  }

DONE:
  if ((charset == CHARSET_filename || charset == CHARSET_include)
     && wl > 1
     && *--wp == ':')
  {
    *wp= 0;
    wl--;
  }

  return wl;
}
