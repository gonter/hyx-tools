/*
 *  FILE %ned/11/ned1102.c
 *
 *  Such- und Ersetzungsfunktionen
 *
 *  written:       1988 09 20
 *                 1989 06 18
 *                 1991 09 11: Revision
 *  latest update: 1998-08-15 14:34:02
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_find ()
{
  ned_ws_find_replace_dialog (aw, 1);
}

/* ------------------------------------------------------------------------ */
void vi_find_forward ()
{
  vi_find (aw, 0);
}

/* ------------------------------------------------------------------------ */
void vi_find_backward ()
{
  vi_find (aw, 1);
}

/* ------------------------------------------------------------------------ */
void pico_find ()
{
  char *pattern;

  if ((pattern= ned_prompt_find ("Find: ")) == (char *) 0) return;

  ned_jmp_pattern (aw, aw->WC_act, pattern, 0);
}
