/*
 *  FILE %ned/03/ned0324.c
 *
 *  NEDa1_interpreter
 *
 *  written:       1990 01 20: aus Modul NED00.C isoliert
 *                 1991 01 29: Revision
 *  latest update: 1997-10-26 10:26:59
 *  $Id: ned0324.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <signal.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"
#ifdef USE_MOUSE
#include <gg/maus.h>
#endif

extern int CMD_TBL [];
extern char PGM [];
extern int pfx;
extern int key;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void NEDa1_interpreter ()
{
  int pfx_c= 0;

  for (;;) /* Editor Hauptschleife: Tasten lesen und auswerten ----- */
  {
    if (pfx == P_FUNCT) pfx = 0;
    if (pfx) if (pfx_c) pfx = pfx_c = 0;
             else             pfx_c++;
    background ();
    setcup     (aw);

#ifdef USE_MOUSE
    key= ned_check_mouse ();
#else
    key= (*nextchar) ();
#endif

    if (key < 0x0200)
       if (pfx < N_PFX)
       {
         NEDa2_interpreter (& PGM [CMD_TBL [pfx* 0x0200 + key]]);
       }
       else p_ins ();              /* ^P: Sondercode */

#ifdef USE_MOUSE
        maus_enable ();
#endif
  }
}
