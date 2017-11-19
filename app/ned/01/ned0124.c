/*
 *  FILE %ned/01/ned0124.c
 *
 *  display status information (e.g. the status line) about a window
 *
 *  written:       1987 04 08
 *                 1991 01 31: Revision
 *  latest update: 2000-09-01 17:51:52
 *  $Id: ned0124.c,v 1.2 2000/09/01 19:20:25 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdio.h>
#include <gg/keys.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"
#include <gg/window.h>

extern int MPflag;
extern int mess_ttl;
extern int mess_lin;
extern char *PFX_XX [];
extern int akt_page;
extern int pfx;
extern int block_mode;
extern int COL_STATUS;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
static int DEBline = 0;    /* Debug-Zeile */

static char *OFF_ON []= { "OFF", "ON" };
static char *BLK_MD []= { "???", "STD", "LINE", "BOX" };
static char *INS_MD []= { "OVR", "INS", "CW " };

static char status [100];
static char *untitled= "<untitled>";

/* ------------------------------------------------------------------------ */
void background ()
{
  if (MPflag
#ifndef USE_TK
      || kbhit ()
#endif
     ) return;

  window_status (aw);
}

/* ------------------------------------------------------------------------ */
void window_status (register struct WINDOWCTRL *w)
{
  char *fileentry;
  register struct LINE *l;
  int flg_0x0D= 'x';

  if (w == (struct WINDOWCTRL *) 0) return;

  if ((l= w->WC_act) != (struct LINE *) 0)
    flg_0x0D= (l->line_flg & LINE_CODE_0x0D) ? 'C' : 'c';

  if (mess_ttl > 0)
  {
    if (mess_ttl == 1) restore_message_line ();
    mess_ttl--;
  }

  if (w->WC_title_short != (char *) 0)
  {
    fileentry= w->WC_title_short;
  }
  else
  {
    if (w->file_type == FTY_HYPER)
    {
      fileentry = ((struct FRAMECTRL *) w->file_or_frame == (void *) 0)
                ? untitled
                : ((struct FRAMECTRL *) w->file_or_frame)->frame_name;
    }
    else
    {
      fileentry = ((struct FILECTRL *) w->file_or_frame == (void *) 0)
                ? untitled
                : ((struct FILECTRL *) w->file_or_frame)->FC_fnm_txt;
    }
    w->WC_title_short= strdup (fileentry); /** ??? **/
#ifdef USE_TK
    ned_tk_set_window_name (w, w->WC_title_short);
#endif /* USE_TK */
  }

  sprintf (status,
           "%s   L:%4d %c:%4d (0x%02X) L=%3d %s %s %1.50s",
           PFX_XX [pfx],
           w->znr,
           flg_0x0D,
           w->cx + w->hv - w->ax,
           get_txt_visible (l, w->cx + w->hv - w->ax),
           (l == (struct LINE *) 0) ? 0 : l->lng,
           INS_MD [w->ins_flg],
           (w->ai) ? "AI"  : "  ",
           fileentry);

/* Note: File or frame information must be limited to 50 bytes here:        */
/* sizeof (status) = 100, 45 characters fixed status info, makes 55         */
/* characters for the filename itself maximum.                              */

#ifdef USE_TK
  tk_draw_string (w, NED_TK_GC_StatusLine, w->ax+4, w->ay-1, status);
#else
  w_setstring (akt_page, w->ax+4, w->ay-1, w->bx, w->ay-1,
               COL_STATUS, status, 0x01);
#endif

#ifdef DEBUG
  switch (DEBline)
  {
    case 0:
      sprintf (status,
        "F: %06lx ->n %06lx ->p %06lx || A: %06lx ->n %06lx ->p %06lx",
        w->first,
        (w->first == (struct LINE *) 0) ? (struct LINE *) 0 : (char *) w->first->next,
        (w->first == (struct LINE *) 0) ? (struct LINE *) 0 : (char *) w->first->prev,
        l,
        (l == (struct LINE *) 0) ? (struct LINE *) 0 : (char *) l->next,
        (l == (struct LINE *) 0) ? (struct LINE *) 0 : (char *) l->prev);
      break;
    case 1:
      sprintf (status,
        "ax %3d ay %3d bx %3d by %3d cx %3d cy %3d Z %3d",
        w->ax, w->ay, w->bx, w->by, w->cx, w->cy, w->znr);
      break;
    case 2:
      sprintf (status,
        "BEG %6lx %5d  END %6lx %5d, flags %04x",
        b_beg.ptr, b_beg.offset, b_end.ptr, b_end.offset,
        (w->WC_act == (struct LINE *) 0) ? 0 : w->WC_act->line_flg);
      break;
  }

  w_setstring (akt_page, 0, 1, 79, 0, COL_STATUS, status, 0x01);
#endif

  return;

#ifdef JUNK
SHORT:
  sprintf (status, "%4d Column %4d", w->znr, w->cx + w->hv - w->ax);
  w_setstring (akt_page, 10, 0, 25, 0, COL_STATUS, status, 0x01);
#endif
}

/* ------------------------------------------------------------------------ */
void back2ground ()    /* Extended Status Line */
{
  register struct WINDOWCTRL *w;
  register struct LINE       *l;

  if (kbhit ()) return;
  if ((w= aw) != (struct WINDOWCTRL *) 0) l= w->WC_act;
  sprintf (status,
           "Indent=%-3.3s  Block=%-4.4s  HV=%4d  f_upd=%2d  edit_mode=%2d",
           OFF_ON [w->ai % 2],
           BLK_MD [block_mode],
           w->hv,
           w->f_upd,
           w->WC_edit_mode);

  w_setstring (0, 0, mess_lin, 79, mess_lin, COL_STATUS, status, 0x01);
  mess_ttl = 7;
}

/* ------------------------------------------------------------------------ */
void QQdeb ()
{
  DEBline= (DEBline + 1) % 3;
  w_setnchar (0, 0, 1, COL_STATUS, ' ', 80);
}
