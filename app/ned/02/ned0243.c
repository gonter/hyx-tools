/*
 *  FILE %ned/02/ned0243.c
 *
 *  Window oeffnen und linken
 *
 *  written:       1995-10-01
 *  latest update: 1997-01-26 12:34:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/window.h>

static int vi_bell_mode= 1;

/* ------------------------------------------------------------------------ */
void vi_bell ()
{
  switch (vi_bell_mode)
  {
    case 0:
      break;

    default:
      w_bell ();
  }
}

/* ------------------------------------------------------------------------ */
void vi_set_bell_mode (int mode)
{
  vi_bell_mode= mode;
}
