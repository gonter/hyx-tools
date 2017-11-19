/*
 *  FILE %ned/07/ned0756.c
 *
 *  paste the current date into the current window
 *
 *  written:       1995-11-28
 *  latest update: 1996-06-09 17:21:37
 *  $Id: ned0756.c,v 1.2 2002/06/15 04:35:20 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int ned_paste_file_name ()
{
  return ned_paste_string (aw->WC_title_short, 0, (char *) 0, (char *) 0);
}
