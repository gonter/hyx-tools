/*
 *  FILE %ned/04/ned0422.c
 *
 *  written:       1990 01 12
 *  latest update: 1996-05-23 18:17:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern int akt_page;
extern int mess_lin;
extern int mess_ttl;

/* ------------------------------------------------------------------------ */
void ned_show_author ()
{
  w_setstring (akt_page, 0, mess_lin, 79, mess_lin,
               WV_ROT | W_HELL | W_BLINK | WH_WEISS,
"This program was written by g.gonter@ieee.org /// distribute freely ///",
  0x01);

  mess_ttl= 16;
}
