/*
 *  FILE %ned/07/ned0754c.c
 *
 *  paste the current date into the current window
 *
 *  written:       1995-11-28
 *  latest update: 1997-04-29 10:43:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/dates.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_paste_date_time ()
{
  char d [80];
  actual_datim (d, DATIMfmt_date_time);
  return ned_paste_string (d, 0, (char *) 0, (char *) 0);
}
