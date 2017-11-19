/*
 *  FILE %ned/04/ned0425.c
 *
 *  Window Control Block fuer gegebenes File suchen
 *
 *  written:       1991 06 25: Revision
 *  latest update: 1997-06-11 14:22:06
 *  $Id: ned0425.c,v 1.2 2004/05/08 15:41:39 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *windows;

/* ------------------------------------------------------------------------ */
int find_file (
char *fnm,
char *current_path,
char **real_fnm,
char **virtual_fnm)
{
  struct WINDOWCTRL *w;
  struct FILECTRL *fc;
  int wn= 1;
  int rv= -1;
  char *r_fnm;
  char *v_fnm;

  if (find_virtual_file (fnm, current_path, real_fnm, virtual_fnm) != 0)
    return -1;

  r_fnm= *real_fnm;
  v_fnm= *virtual_fnm;

  for (w= windows; w != (struct WINDOWCTRL *) 0; w= w->WC_next)
  {
    if (w->file_type == FTY_PLAIN
        && (fc= (struct FILECTRL *) w->file_or_frame) != (struct FILECTRL *) 0
       )
    {
      if (strcmp_nn (fc->FC_fnm_txt, r_fnm) == 0
          || strcmp_nn (w->WC_title_short, v_fnm) == 0
         )
        rv= wn;
    }

    w->wc_window_number= wn++;
  }

  return rv;
}
