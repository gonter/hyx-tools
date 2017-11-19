/*
 *  FILE %ned/08/ned0807.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1999-04-25 16:32:33
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifndef MSDOS
#include <stdio.h>      /* HP/UX: defines size_t for malloc */
#endif
#include <stdlib.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void p_feature_reset ()
{
  struct FEATURE *f, **f2;

  if ((f2= ned_feature_find3 (0)) == (struct FEATURE **) 0) return;

  aw->f_upd= 1;
  f= *f2;
  *f2= f->ftr_next;

  /* Text Segmente und LINE freigeben ############# */
  free (f);
  wd_displine (aw, aw->WC_act, aw->cy, aw->ax, aw->bx);
}
