/*
 *  FILE %ned/08/ned0811.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1987 09 08
 *                 1991 02 07: Revision
 *  latest update: 1996-07-26  3:14:19
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void q_save_marker (FILE *fo, struct MARKER *m)
{
  if (m->ptr == (struct LINE *) 0)
       fprintf (fo, " 0    0   0\n");
  else fprintf (fo, "%2d %4d %3d\n",
                /* m->fptr->num **** window ID **** */ 0,
                ned_cnt_line_2beg (m->ptr),
                m->offset);
}
