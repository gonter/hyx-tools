/*
 *  FILE %ned/04/ned0423.c
 *
 *  written:       1996-05-23
 *  latest update: 1998-08-16 12:39:43
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern char NED_VERSION [];

/* ------------------------------------------------------------------------ */
void ned_show_version ()
{
  ned_message_2 ("Version ", NED_VERSION);
}
