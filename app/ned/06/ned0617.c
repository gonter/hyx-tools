/*
 *  FILE ~/usr/ned/06/ned0617.c
 *
 *  File- and Windowoperations
 *  >> reads in the password used for garbling option.
 *
 *  >>>> NOT USED ANY LONGER <<<<
 *
 *  written:       1987 04 08
 *                 1991 02 03: Revision
 *  latest update: 1997-06-17 10:57:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "message.h"
#include "proto.h"

extern int oper_level;
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_garbling_code ()         /* ^K -: File Schluessel eingeben           */
{
  char fnm [32];
  int i;

  if (oper_level >= LEV_FNM) return;
  if (aw->file_or_frame == (void *) 0) return;              /* siehe oben */
  if (aw->file_type == FTY_HYPER) return;
  fnm [0]=0;
  if (rd_str ("New Code: ", fnm, 32) == -1) return;

  for (i = 0; i < 30; i++)
     ((struct FILECTRL *) aw->file_or_frame)->garbling_code [i] = fnm [i];
  /* Damit werden alle Windows, die auf dieses File angehaengt sind  */
  /* automatisch anders codiert !!                                   */
}
