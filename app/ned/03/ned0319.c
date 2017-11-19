/*
 *  FILE %ned/03/ned0319.c
 *
 *  NED_interpreter: main interpreter that handles all sorts of
 *    arriving events, such as key press, signals, mouse events etc.
 *
 *  written:       1990 01 20: aus Modul NED00.C isoliert
 *                 1991 01 29: Revision
 *                 1991 06 01: Revision
 *                 1993-07-31: vi mode
 *  latest update: 1999-05-01 13:42:22
 *  $Id: ned0319.c,v 1.4 2004/05/08 15:41:39 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
int (*cdecl P_TBL []) (void);
#endif

#include <signal.h>
#include <stdio.h>
#include "ed.h"
#include "proto.h"
#ifdef USE_MOUSE
#include <gg/maus.h>
#endif
#include <gg/window.h>

extern int (*P_TBL []) (void);
extern int pfx;
extern int key;
extern int repeat;
extern int ptbl_offset;
extern ned_input_handler *nextchar;  /* Editor Eingabe: KBD | FILE ..            */
extern struct WINDOWCTRL *aw;

static int std_pfx= P_NONE;     /* normal editor mode */

static int signal_flag= 0;

/* ------------------------------------------------------------------------ */
void NED_interpreter ()
{
  int pfx_c;
  pfx= std_pfx;

  set_sig ();

  for (;;) /* Editor Hauptschleife: Tasten lesen und auswerten ----- */
  {
    background ();
    setcup (aw);

    if (signal_flag)
    {
      signal_flag= 0;
      w_sig_winch ();

      setup_screen ();
      ned_window_size (aw, 5, 1);
      ned_w_jmp_aktline (aw, NEDJMP_LINE_3, 0, NEDJMP_FLAG_REDRAW);
    }

#ifdef USE_MOUSE
    key= check_maus ();
#else
    key= (*nextchar) ();
#endif /* USE_MOUSE */
    if (key < 0) continue;

    pfx_c= pfx;
    pfx= std_pfx;

    if (pfx_c < N_PFX)
    {
      ptbl_offset= pfx_c*128 + key;
      (*P_TBL [ptbl_offset]) ();
    }
#ifdef __OLD__ /* 1997-01-05 11:49:24 */
    else p_ins ();              /* ^P: Sondercode */
#endif /* __OLD__ 1997-01-05 11:49:24 */

#ifdef USE_MOUSE
    maus_enable ();
#endif

    if (key < '0' || key > '9') /* && in vi mode T2D */
      repeat= 0;
  }
}

/* ------------------------------------------------------------------------ */
void vi_on ()
{
#ifdef USE_ABBREVIATIONS
  ned_check_abbrev ();
#endif /* USE_ABBREVIATIONS */

  ned_message_1 ("switching to vi mode!");
  std_pfx= pfx= P_VI;
  ned_set_marker (aw, '.');
}

/* ------------------------------------------------------------------------ */
void vi_ins ()
{
  ned_wc_ins_mode (aw, INSFLG_insert);
}

/* ------------------------------------------------------------------------ */
void vi_ovr ()
{
  ned_wc_ins_mode (aw, INSFLG_overwrite);
}

/* ------------------------------------------------------------------------ */
void ned_wc_ins_mode (struct WINDOWCTRL *wc, int mode)
{
  if (wc != (struct WINDOWCTRL *) 0) wc->ins_flg= mode;
  std_pfx= pfx= P_NONE;
  /*** ned_set_marker (wc, ','); ***/
}

/* ------------------------------------------------------------------------ */
void misc_sig (int sig)
{
  signal_flag= sig;
}

/* ------------------------------------------------------------------------ */
int set_sig (void)
{
  signal (SIGWINCH, &misc_sig);
  return 0;
}
