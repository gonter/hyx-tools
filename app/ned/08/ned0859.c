/*
 *  FILE ~/usr/ned/08/ned0859.c
 *
 *  written:       1991 06 25
 *  latest update: 1994-07-10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int eval_ned_parameter (char *str, int option)
{
#ifdef MSDOS
  option;
#endif

  return eval_window_parameters (aw, str);
}
