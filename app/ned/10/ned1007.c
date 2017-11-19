/*
 *  FILE %ned/10/ned1007.c
 *
 *  Maus Steuerung
 *
 *  written:       1990 01 28
 *                 1991 02 03: Revision
 *                 1991 05 27: Revision
 *  latest update: 1999-04-25 16:36:25
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif

#include <stdlib.h>
#include "ed.h"
#include "edhyx.h"
#ifdef MSDOS
#include <gg/window.h>
#endif
#include <gg/maus.h>
#include <gg/keys.h>
#include "proto.h"

extern int W_TEXT_CELL_X;
extern int W_TEXT_CELL_Y;

extern struct WINDOWCTRL *windows;
extern int maus_angeschlossen;
extern int akt_page;

#ifdef MSDOS
static char *blit_p1= (char *) 0;
static int blit_p1_size= 0;
#endif

#define BOX_BX      60
#define BOX_MEMORY 124  /* BOX_BX*2+4 Platzbedarf in Byte je Box-Zeile      */

/* ------------------------------------------------------------------------ */
int q_window_menu ()
{
  int wn= -1;
#ifdef MSDOS
  struct WINDOWCTRL *w;
  int cnt= 0;
  int m= 0;
  int s;
  int x, y, t;
  char *fnm;
  int color;                    /* Farbe der Frame Anzeige */

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next) cnt++;

  s= (cnt+2)*BOX_MEMORY;
  if (s > blit_p1_size)
  {
    if (blit_p1_size) free (blit_p1);
    blit_p1= (char *) malloc (blit_p1_size= s);
    if (blit_p1 == (char *) 0) return -1;
  }

  w_blit_save (blit_p1, akt_page, 0, 2, BOX_BX, cnt+3);
  w_disp_bbox (akt_page, 0, 2, BOX_BX, cnt+3, WV_ROT|W_HELL|WH_VIOLETT, 2);

  s= 3;
  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
  {
    wd_show_wdnr (akt_page, 1, s, WV_GELB | WH_VIOLETT, s-2);

    if (w->WC_title_short != (char *) 0)
    {
      fnm= w->WC_title_short;
    }
    else
    if (w->file_or_frame != (void *) 0)
    {
      fnm= (w->file_type == FTY_HYPER)
          ? ((struct FRAMECTRL *) w->file_or_frame)->frame_name
          : ((struct FILECTRL  *) w->file_or_frame)->FC_fnm_txt;
    }
    else fnm= "<untitled>";

    color= (w->file_type == FTY_HYPER)
          ? WV_KOBALT | W_HELL | WH_VIOLETT
          : WV_WEISS  | W_HELL | WH_VIOLETT;

    w_setstring (akt_page, 5, s, BOX_BX-1, s, color, fnm, 0x01);
    s++;
  }

  if (maus_angeschlossen) maus_enable ();

  for (;;)
  {
    if (maus_angeschlossen)
    {
      maus_position (&x, &y, &t);
      x /= W_TEXT_CELL_X;
      y /= W_TEXT_CELL_Y;
      switch (t)
      {
        case -1:
          maus_angeschlossen= 0;
          break;
        case 1:
          if (x > 0 && x < BOX_BX && y > 2 && y < cnt+3)
          {
            wn= y-2;
          }
        case 2:
          m= 1;
          goto OVER;
      }
    }

    if (kbhit ())
    {
      switch (t= kbin ())
      {
        case 0x1B:
          goto OVER;
        case '1': case '2': case '3':
        case '4': case '5': case '6':
        case '7': case '8': case '9':
          wn= t-'0';
          goto OVER;
        case K_PF1: case K_PF2: case K_PF3: case K_PF4:
        case K_PF5: case K_PF6: case K_PF7: case K_PF8:
        case K_PF9: case K_PF10:
          wn= t-K_PF1+1;
          goto OVER;
        case K_PF11:
          wn= 11;
          goto OVER;
        case K_PF12:
          wn= 12;
          goto OVER;
      }
    }
  }

OVER:
  if (maus_angeschlossen) maus_disable ();
  w_blit_load (blit_p1, akt_page, 0, 2, BOX_BX, cnt+3);
  if (maus_angeschlossen) maus_enable ();
  if (m) while (t) maus_position (&x, &y, &t);
#else
#ifdef USE_TK
  mac_call_tcl ("show_window_list");
#endif /* USE_TK */
#endif /* !MSDOS */

  return wn;
}
