/*
 *  FILE %ned/04/ned0421.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1996-01-06 11:15:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#include <gg/keys.h>
#include <gg/window.h>

extern int akt_page;
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
void p_XX_break ()
{
#ifdef MSDOS
  /* Keyboard Puffer entleeren              */
  /* CTRL-BREAK bleibt sonst im Puffer      */
  /* das fuehrt zu einem dead lock          */

  w_setstring (akt_page, 0, 2, 79, 2,
               WV_ROT | W_HELL | W_BLINK | WH_WEISS,
               "Hit any key", 0x01);

  kbin ();
#endif /* MSDOS */
}
