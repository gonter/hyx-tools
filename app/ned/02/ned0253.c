/*
 *  FILE %ned/02/ned0253.c
 *
 *  compatibility mode: WordStar table for insert
 *
 *  written:       1996-05-16
 *  latest update: 1997-02-20 12:45:35
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/strings.h>

extern int (*P_TBL []) (void);
extern int (*P_TBL_WordStar []) (void);
extern char *PFX_XX [];
extern char *PFX_QUOTE;

/* ------------------------------------------------------------------------ */
void wordstar_mode ()
{
  int i;

  for (i= 0; i < TBL_CTRL_SIZE; i++)
    P_TBL [i]= P_TBL_WordStar [i]; 

  PFX_XX [0]= "WS";
  PFX_QUOTE= "^P";
  vi_ins ();            /* just in case, also switch to insert mode         */
}

