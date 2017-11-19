/*
 *  FILE %ned/08/ned0866.c
 *
 *  written:       1991 07 05
 *  latest update: 2001-02-11 11:10:06
 *  $Id: ned0866.c,v 1.2 2001/02/12 00:03:34 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* #define DEBUG */
#ifdef DEBUG
#include <stdio.h>
#endif

/* ------------------------------------------------------------------------ */
int show_feature (struct FEATURE *fp)
{
#define LIN_SIZ 80
  char lin [LIN_SIZ];
  struct LINE *l;

  if (fp == (struct FEATURE *) 0
      || (l= fp->ftr_text_line) == (struct LINE *) 0
     ) return -1;

#ifdef DEBUG
  sprintf (lin, "ty=%d w=%d dm=%d c=0x%04X ras=%d",
           fp->ftr_type, fp->ftr_weight, fp->ftr_display_mode,
           fp->ftr_colour, fp->ftr_replarray_size);
  ned_message_1 (lin);
#else
  if (ned_line_2_string (l, 0, l, l->lng, lin, LIN_SIZ, 0L, 0x0000)
      != (char *) 0)
    ned_message_1 (lin);
#endif

  return 0;
}
