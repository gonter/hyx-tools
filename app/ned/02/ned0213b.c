/*
 *  FILE %ned/02/ned0213b.c
 *
 *  Bildschirmaufbau
 *  -  resize one ore more windows
 *
 *  written:       1987 04 08
 *                 1994-05-23: isolated from ned0213.c
 *  latest update: 2000-08-25 19:31:22
 *  $Id: ned0213b.c,v 1.3 2000/08/25 18:05:45 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void q_wdwsize (int k)
{
  struct WINDOWCTRL *xw;

#ifdef USE_TK
  switch (k)
  {
    case '-': case '+':
    case 's': case 'S':
    case 't': case 'T':
      if ((xw= winstack_get (1)) == (struct WINDOWCTRL *) 0)
        break;

      switch (k)
      {
        case '-':
        case 's':
        case 't':
          ned_tk_window_dock (xw, aw, 't');
          break;
        default:
          ned_tk_window_dock (aw, xw, 't');
          break;
      }
      break;
  }
#else
  int pos1, pos2;

  switch (k)
  {
    case '/':
    case 'f': case 'F':
      ned_clear_screen ();
      p_wdwfaecher ();
      break;

    case '-': case '+':
    case 's': case 'S':
    case 't': case 'T':
      switch (k)
      {
        case '-':
        case 's':
        case 't':
          pos1= 2;
          pos2= 8;
          break;
        default:
          pos1= 8;
          pos2= 2;
          break;
      }

      if ((xw= winstack_get (1)) == (struct WINDOWCTRL *) 0)
        pos2= 0;
      else /* setup previous window */
      {
        get_window_number (xw);
        q2_wdwsize (xw, pos1);
      }

      /* setup current window */
      q2_wdwsize (aw, pos2);
      break;

    default:
      if (k >= '0' && k <= '9')
        q2_wdwsize (aw, k-'0');
      break;
  }
#endif /* !USE_TK */
}
