/*
 *  FILE %ned/03/ned0302.c
 *
 *  elementare Editierfunktionen
 *
 *  written:       1987 04 08
 *                 1991 01 29: Revision
 *  latest update: 1996-07-26  3:34:42
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
extern int word_wrap_count;

/* ------------------------------------------------------------------------ */
void p_ww ()                    /* ^O^A: Enter Word Wrap Count              */
{
  int xwwc;
  char puffer [40];

  if (aw->WC_act == (struct LINE *) 0) return;

  puffer [0]= 0;
  if (rd_str ("Word Wrap Column: ", puffer, 40) == -1) return;
  xwwc= (int) get_parameter_value (puffer);
  aw->wwc= word_wrap_count= (xwwc <= 0) ? LINE_LNG_TXT : xwwc;
}
