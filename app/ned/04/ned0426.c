/*
 *  FILE %ned/04/ned0426.c
 *
 *  call command processor to execute program
 *
 *  written:       1992 01 01
 *  latest update: 1996-10-29 20:09:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int W_TEXT_MAX_Y;
extern int akt_page;

/* ------------------------------------------------------------------------ */
void q_shell (char *command_line)
{
  if (command_line == (char *) 0 || *command_line == 0)
#ifdef MSDOS
    command_line= "command";    /* MSDOS command line interpreter           */
#else
#ifdef USE_TK
    return;                     /* TK would have to open a window for shell */
#else
    command_line= "sh";         /* T2D: setup for other shell ??            */
#endif /* !USE_TK */
#endif /* !MSDOS */

  /* w_col80mode (); */
  w_setcup (akt_page, 0, W_TEXT_MAX_Y-1);
  system (command_line);
#ifdef MSDOS
  restore_window_mode ();
#endif /* MSDOS */
  p_refresh_all ();
}
