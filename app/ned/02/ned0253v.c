/*
 *  FILE %ned/02/ned0253v.c
 *
 *  compatibility mode: vi table for insert
 *
 *  written:       1996-12-03
 *  latest update: 1999-05-02 11:14:28
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
extern int (*P_TBL_VI []) (void);
extern char *PFX_XX [];
extern char *PFX_QUOTE;

/* ------------------------------------------------------------------------ */
void vi_mode ()
{
  int i;

  for (i= 0; i < TBL_CTRL_SIZE; i++)
    P_TBL [i]= P_TBL_VI [i]; 

  PFX_XX [0]= "vi";
  PFX_QUOTE= "^V";
  vi_on ();
}
