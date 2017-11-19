/*
 *  FILE %ned/04/ned0410.c
 *
 *  File I/O: Save- /Load-File
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1998-08-16 12:31:37
 *  $Id: ned0410.c,v 1.5 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern struct FILECTRL *files;
extern struct WINDOWCTRL *aw;
extern struct WINDOWCTRL *windows;
extern int oper_level;

/* ------------------------------------------------------------------------ */
void p_ssave ()
{
  int rc= 0;

  if (oper_level >= LEV_FIO) return;

#ifdef JUNK
{
  char lin[80];
  sprintf (lin, "p_save: files=%08lX ->next=%08lX aw->f_upd=%d",
  files,
  (files == (struct FILECTRL *) 0) ? (struct FILECTRL *) 0 : files->next,
  aw->f_upd);
  ned_error_message (lin);
}
#endif

  if (aw->file_type == FTY_FTRWDW)
  {
    if (aw->f_upd && aw->feature_window != (struct WINDOWCTRL *) 0)
      aw->feature_window->f_upd= 1;
  }
  else
  {
    if (active_feature_window (aw) != (struct WINDOWCTRL *) 0)
    { /* aktuelles Window hat ein aktives(!) Feature Window! */
      ned_message_1 ("feature window is active!");
      return;
    }
  }

  if (windows->next == (struct WINDOWCTRL *) 0)
  {
    printf ("ned0410: windows->next == NULL; exiting...\n");
    if (aw->f_upd) p_sx ();
    else p_exit ();
  }
  else
  {
    if (aw->file_or_frame != (void *) 0)
    {
      if (aw->f_upd) rc= ned_w_save (aw, 1);
      if (rc == 0) ned_wc_abandon (aw);
    }

    if (rc == 0) ned_close_window ();
  }
}

/* ------------------------------------------------------------------------ */
void ned_ssave_all ()
{
  struct WINDOWCTRL *wc1, *wc2= (struct WINDOWCTRL *) 0;

  while ((wc1= aw) != (struct WINDOWCTRL *) 0)
  {
    if (wc1 == wc2) break; /* no change since lanst call! */
    wc2= wc1;
    p_ssave ();
  }
}
