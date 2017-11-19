/*
 *  FILE %ned/ned0610e.c
 *
 *  open a window for a give filename
 *
 *  written:       1996-07-14 extracted from ned0610c.c
 *  latest update: 2001-02-11 21:23:57
 *  $Id: ned0610e.c,v 1.4 2001/02/12 00:03:31 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gg/filename.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int default_edit_mode;
extern int default_bin_eoln;
extern int default_bin_llng;

/* ------------------------------------------------------------------------ */
int ned_open_file_2 (
struct WINDOWCTRL *wc,
char *fnm,
int flags)        /* NED_OPENF_*              */
{
  char *real_fnm= (char *) 0;
  char *virtual_fnm= (char *) 0;
  int rc= -1;
  int wn;
  struct stat st;

  if (*fnm == 0) return -1;

  if ((wn= find_file (fnm,
                      (flags & NED_OPENF_NO_REL_PATH)
                      ? (char *) 0
                      : ned_get_file_path (wc),
                      &real_fnm, &virtual_fnm)) != -1)
  {
    q_jmpwdw (wn);
    goto CNT;
  }

  if (real_fnm != (char *) 0)
  {
    if ((flags & NED_OPENF_EXISTS) && stat (real_fnm, &st) != 0) goto RETURN;
    /* T2D: setup or so, open only existing files! */
    fnm= real_fnm;
  }

  /* window with loadable file does not exist, so create one and load file */
  q_jmpwdw (p_wdwopen ());
  q_fnm (fnm);

  if (flags & NED_OPENF_SGML) aw->file_format= FMT_SGML;
  else if (flags & NED_OPENF_BINARY)
  {
    aw->file_format= FMT_BINARY;
    aw->bin_eoln= default_bin_eoln;     /* End-Of-Line Code                 */
    aw->bin_llng= default_bin_llng;     /* Laenge von binaeren Zeilen       */
  }
  aw->WC_edit_mode= default_edit_mode;
  if (flags & NED_OPENF_READ_ONLY) aw->WC_edit_mode;
  s_fget (aw);

CNT:
  if (flags & NED_OPENF_REDRAW)  ned_display_window (aw);
  if (flags & NED_OPENF_HISTORY) take_history_notes (aw);
  rc= 0;

RETURN:
  free_or_what (real_fnm);
  free_or_what (virtual_fnm);

  return rc;
}
