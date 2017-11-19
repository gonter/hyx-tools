/*
 *  FILE %ned/05/ned0503.c
 *
 *  elementare Editierfunktionen: TAB, NL, PGUP, PGDN
 *
 *  written:       1987 04 08
 *                 1991 09 19: Revision
 *  latest update: 1996-11-03 17:36:52
 *  $Id: ned0503.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern char *default_help_cluster;
extern char *default_help_jump_to_line;

/* ------------------------------------------------------------------------ */
void ned_pr_jump_to_line ()
{
#define LN_SIZE 32
  char line_number [LN_SIZE];

  if (aw->WC_act == (struct LINE *) 0) return;

  line_number [0]= 0;
  ned_prompt_string ("Zeile #", line_number, LN_SIZE,
                     default_help_cluster,
                     default_help_jump_to_line,
                     ned_cb_jump_to_line,
                     (void *) aw);
}
