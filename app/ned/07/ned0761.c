/*
 *  FILE %ned/07/ned0761.c
 *
 *  copy block
 *
 *  written:       1996-03-06
 *  latest update: 1997-10-26 10:49:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_markup_block_prompt ()
{
#define MAX_TAG 80
  char tagging_sequence [MAX_TAG];

  tagging_sequence [0]= '<';
  tagging_sequence [1]= 0;
  if (rd_str ("tag: ", tagging_sequence+1, MAX_TAG-2) != -1)
  {
    int i;

    i= strlen (tagging_sequence);
    tagging_sequence [i++]= '>';
    tagging_sequence [i++]= 0;
    ned_markup_block_2 (aw, tagging_sequence);
  }
}
