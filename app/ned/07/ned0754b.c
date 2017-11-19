/*
 *  FILE %ned/07/ned0754b.c
 *
 *  paste the current date into the current window
 *
 *  written:       1997-04-29
 *  latest update: 1997-04-29 10:34:37
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dates.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_paste_seconds ()
{
  char d [80];
  actual_datim (d, DATIMfmt_seconds);
  return ned_paste_string (d, 0, (char *) 0, (char *) 0);
}
