/*
 *  FILE %ned/07/ned0754d.c
 *
 *  paste the current date into the current window
 *
 *  written:       1995-11-28
 *  latest update: 1997-11-28 12:39:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/dates.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_paste_date_string ()
{
  char d [80];
  char *TZ;

  if ((TZ= getenv ("TZ")) == (char *) 0) TZ= "CET";

  prepare_date (d, TZ, 80);
  return ned_paste_string (d, 0, (char *) 0, (char *) 0);
}
