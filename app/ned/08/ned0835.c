/*
 *  FILE %ned/08/ned0835.c
 *
 *  prompt for a string and evaluate it
 *  (hardly used function!)
 *
 *  written:       1991 05 23
 *  latest update: 2001-02-11 12:49:23
 *  $Id: ned0835.c,v 1.2 2001/02/12 00:03:33 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void ned_eval_str ()
{
  char str [80];

  str [0]= 0;
  if (rd_str ("Eval: ", str, 80) == -1) return;
  ned_eval_string (str, 0);
}
