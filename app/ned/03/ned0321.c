/*
 *  FILE %ned/03/ned0321.c
 *
 *  Umschalten des 0x0D Flags in der aktuellen Zeile
 *
 *  written:       1990 11 01
 *                 1991 01 29: Revision
 *  latest update: 1996-05-23 17:46:40
 *  $Id: ned0321.c,v 1.2 2001/08/26 23:27:14 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_line_end_MAC ()
{
  if (aw == (struct WINDOWCTRL *) 0) return;

  ned_line_end_UNIX ();
  aw->bin_eoln= 0x0D;
}
