/*
 *  FILE %ned/02/ned0204g.c
 *
 *  written:       2002-06-08
 *  latest update: 2002-06-08 11:44:40
 *  $Id: ned0204g.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include "ed.h"
#include <gg/window.h>
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_line_info (void)
{
  struct FILECTRL *fc;
  char *fileentry;
  char info[80];
  char *modinfo;

  if (aw == (struct WINDOWCTRL *) 0
      || (fc= (struct FILECTRL *) aw->file_or_frame) == (struct FILECTRL *) 0
     ) return;

  fileentry= aw->WC_title_short;
  if (fileentry == (char *) 0) fileentry= "???";

  aw->tlines= ned_cnt_total_lines (aw->WC_act);
  if (aw->tlines)
  {
    sprintf (info, "%d of %d [%d%%]", aw->znr, aw->tlines,
             aw->znr*100/aw->tlines);
  }
  else strcpy (info, "empty file");

  modinfo= (aw->f_upd) ? ": " : ": un";

  ned_message_4 (fileentry, modinfo, "modified: line ", info);
}
