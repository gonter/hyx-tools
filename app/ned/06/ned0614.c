/*
 *  FILE %ned/06/ned0614.c
 *
 *  assign a name to a window, either for the first time or rename it.
 *
 *  written:       1987 04 08
 *                 1990 04 01: function of p_fnm (renaming of a unnamed
 *                             window) rolled in.  Thus, the function p_fnm
 *                             itself became obsolete and was removed.  See
 *                             also changes in the editor tables ned0001?.c.
 *                 1991 02 03: revision
 *                 1994-06-19: renamed to ned0614.c as q_rename
 *  latest update: 2000-09-01 18:01:36
 *  $Id: ned0614.c,v 1.3 2000/09/01 19:20:26 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int oper_level;

/* ------------------------------------------------------------------------ */
int ned_rename_file (char *fnm, int max_fnm)
{
  int mode= 1;
  struct FILECTRL *fc;
  int fst;                      /* file status */
  int modified;

  if (oper_level >= LEV_FNM) return 0;

  if ((fc= (struct FILECTRL *) aw->file_or_frame) != (struct FILECTRL *) 0)
  {
    mode= 0;
    strcpy_max (fnm, fc->FC_fnm_txt, max_fnm);
  }

ASK_AGAIN:
  /* new filename: get name of file on cursor position */
  if ((modified= rd_str ((mode) ? "Filename: " : "New Name: ", fnm, max_fnm))
        == -1
      || (fst= editable_file (fnm)) == 0
     )
    return 0;

  if (modified
      && fst == 2
      && get_confirmation ("File exists; replace? (Y|N)", 0) == 1
     ) goto ASK_AGAIN;

  if (mode)
  { /* Filenamen fuer ein unbenanntes Window angeben */
    q_fnm (fnm);
  }
  else
  { /* change a filename */
    aw->WC_title_short= FC_setup_filenames (fc, fnm, (char *) 0);
#ifdef USE_TK
    ned_tk_set_window_name (aw, aw->WC_title_short);
#endif /* USE_TK */
    /* Damit werden alle Windows, die auf dieses File      */
    /* angehaengt sind, automatisch umbenannt !!!!!        */
  }

  aw->f_upd= 1; /* ??? 1996-05-27 19:28:38 */

  return 1;
}
