/*
 *  FILE %ned/02/ned0213a.c
 *
 *  Bildschirmaufbau
 *  Windowoperation: Oeffnen, Schliessen, Verschieben
 *
 *  written:       1987 04 08
 *  latest update: 1997-01-12 17:28:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern int akt_page;
extern int COL_STATUS;
extern struct WINDOWCTRL *aw;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
void p_wdwsize ()
{
  w_setstring (akt_page, aw->ax+4, aw->ay-1, aw->ax+7, aw->ay-1,
               COL_STATUS, "^O^W", 0x01);

  q_wdwsize ((*nextchar) ());
}
