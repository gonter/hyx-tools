/*
 *  FILE %ned/07/ned0758.c
 *
 *  paste the current date into the current window
 *
 *  written:       1995-12-26
 *  latest update: 1996-06-09 17:21:57
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_paste_user ()
{
  char *user;
  if ((user= getenv ("EMAIL")) == (char *) 0) user= "unknown@somewhere";

  return ned_paste_string (user, 0, (char *) 0, (char *) 0);
}
