/*
 *  FILE %ned/06/ned0621.c
 *
 *  File- und Windowoperationen
 *
 *  written:       1987 04 08
 *                 1991 06 01: Revision
 *  latest update: 1997-10-26 10:25:17
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

#ifdef UX_DEBUG
#include <stdio.h>
#endif

extern int COL_ASK;
extern int mess_ttl;
extern int mess_lin;
extern ned_input_handler *nextchar;

/* ------------------------------------------------------------------------ */
int ned_error_message (char *s)
{
#ifdef UX_DEBUG
  printf ("%s\n", s);
#endif

  w_setstring (0, 0, mess_lin, 79, mess_lin, COL_ASK, s, 0x01);
  (*nextchar) ();

  mess_ttl= 2;

  return 0;
}
