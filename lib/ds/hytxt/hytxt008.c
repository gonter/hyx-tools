/*
 *  FILE ~/usr/sgml/hytxt008.c
 *
 *  written:       1991 03 02
 *  latest update: 1994-06-03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hytxt_report_frame (
FILE *fo,
char *txt,
struct HYTXT_FRAME *fd,
int  ret_val)
{

  fprintf (fo, "%s: rc=%d %s\n", txt, ret_val, fd->hytxt_frame_name);
  fprintf (fo, "%s:   %08lX %08lX %08lX %08lX\n",
           txt,
           fd->hytxt_frame_prev,    fd->hytxt_frame_next,
           fd->hytxt_frame_earlier, fd->hytxt_frame_newer);
  fprintf (fo, "%s:   %08lX %08lX\n",
           txt,
           fd->hytxt_frame_pos_beg, fd->hytxt_frame_pos_end);

  return 0;
}
