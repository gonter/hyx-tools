/*
 *  FILE %ned/02/ned0213d.c
 *
 *  Window Tiling Code, originally used in %ned/ned00.c to arrange
 *  windows for more than one window.
 *
 *  written:       1995-10-01
 *  latest update: 1997-10-26 11:09:45
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

#define TOP_LINE 2
extern struct WINDOWCTRL *aw, *windows;;
extern int NED_TEXT_MAX_X, NED_TEXT_MAX_Y;

/* ------------------------------------------------------------------------ */
int ned_tile_window (int argf)
{
  int window_top_line;
  int lines_per_window;
  int i;

  /* windows festlegen */
  aw= windows;
  lines_per_window= (NED_TEXT_MAX_Y-2)/argf;
  window_top_line= TOP_LINE+1;

  for (i= 0; i < argf; i++)
  {
      if (aw->w_upd & 0x80)
      {
        /* Window per Setup-File definiert */
        aw->hv=  0;
        aw->cx= aw->ax;
        aw->cy= aw->ay;
      }
      else
      { /* Window noch undefiniert */
        aw->hv= 0;
        aw->cy=
        aw->ay= window_top_line;
#ifdef MAKE_WINDOW_FRAMES
        aw->ax= 1;
        aw->cx= 1;
        aw->bx= NED_TEXT_MAX_X-2;
        window_top_line += lines_per_window 
                           + ((i) ? 0 : ((NED_TEXT_MAX_Y-2) % argf));
#else
        aw->ax= 0;
        aw->cx= 0;
        aw->bx= NED_TEXT_MAX_X-1;
        window_top_line += lines_per_window
                           + ((i) ? 0 : ((NED_TEXT_MAX_Y-1) % argf));
#endif /* !MAKE_WINDOW_FRAMES */
        aw->by= window_top_line - 3;
      }

      if (aw->next == (struct WINDOWCTRL *) 0) break;
      aw= aw->next;
  }

  if (aw != (struct WINDOWCTRL *) 0           /* letztes Window bekommt   */
      && !(aw->w_upd & 0x80))                 /* den Rest des Schirms.    */
#ifdef MAKE_WINDOW_FRAMES
    aw->by= NED_TEXT_MAX_Y-2;
#else
    aw->by= NED_TEXT_MAX_Y-1;
#endif /* !MAKE_WINDOW_FRAMES */

  return 0;
}
