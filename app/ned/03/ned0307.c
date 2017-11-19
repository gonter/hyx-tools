/*
 *  FILE ~/usr/ned/03/ned0307.c
 *
 *  elementare Editierfunktionen
 *  toggle read only mode, if this is allowed in the first place
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1994-10-16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_insblk ()        /* Ctrl O+      */
{
  if (!(aw->WC_edit_mode & EDIT_NOTOGGLE))
     aw->WC_edit_mode ^= EDIT_READ_ONLY;
}
