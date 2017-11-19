/*
 *  FILE %ned/02/ned0252.c
 *
 *  pico emulation on
 *
 *  written:       1996-05-16
 *  latest update: 1998-08-15 14:30:54
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
extern int (*P_TBL_PICO []) (void);
extern char *PFX_XX [];
extern int block_mode;

/* ------------------------------------------------------------------------ */
void pico_mode ()
{
  int i;

  for (i= 0; i < TBL_CTRL_SIZE; i++)
    P_TBL [i]= P_TBL_PICO [i]; 

  PFX_XX [0]= "PI";
  block_mode= BLOCK_MODE_line;
  vi_ins ();  /* or something else */
  ned_set_ic (1);
}
