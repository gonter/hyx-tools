/*
 *  FILE %ned/06/ned0615.c
 *
 *  File- und Windowoperationen:
 *    Filename ueberpruefen und Datenstruktur anlegen
 *
 *  written:       1987 04 08
 *                 1990 04 01: Revision
 *                 1991 02 03: Revision
 *  latest update: 2000-12-09 13:33:47
 *  $Id: ned0615.c,v 1.3 2000/12/09 17:33:50 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include "ed.h"
#include "message.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern struct FILECTRL *files;

/* ------------------------------------------------------------------------ */
int q_fnm (char *fnm)
{
  struct FILECTRL *f;

  if (fnm [0] == 0
      || aw == (struct WINDOWCTRL *) 0
      || !editable_file (fnm)
      || (f= file_alloc ()) == (struct FILECTRL *) 0
     )
  {
    ned_error_message (ERR_OPEN_FILE);
    return -1;
  }

  aw->WC_title_short= FC_setup_filenames (f, fnm, (char *) 0);
  /*** printf ("0615: title='%s'\n", aw->WC_title_short); ***/
#ifdef USE_TK
  ned_tk_set_window_name (aw, aw->WC_title_short);
#endif /* USE_TK */

  f->FC_links= 1;
  f->FC_prev= f->FC_next= (struct FILECTRL *) 0;
  if (files != (struct FILECTRL *) 0)
  {
    f->FC_next= files;
    files->FC_prev= f;
  }
  files= f;

  aw->file_or_frame= f;
  aw->file_type= FTY_PLAIN;

  return 0;
}
