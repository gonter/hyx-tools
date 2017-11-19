/*
 *  FILE ~/usr/sgml/hytxt007.c
 *
 *  written:       1990 04 13
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
#include <gg/fnames.h>

/* ------------------------------------------------------------------------ */
int hytxt_frame2dta2 (
struct HYTXT_FRAME *fr,
struct dta2_buff **d2)
{
  struct dta2_buff *d;
  *d2 = d = (struct dta2_buff *) calloc (sizeof (struct dta2_buff), 1);
  if (d == (struct dta2_buff *) 0) return -1;

  d->size = fr->hytxt_frame_pos_end - fr->hytxt_frame_pos_beg + 1L;
  sprintf (d->name, "%06lX%06lX",
           fr->hytxt_frame_pos_beg,
           fr->hytxt_frame_pos_end);

  d->infos [0] = malloc (strlen (fr->hytxt_frame_name)+1);
  d->info_allocated = 1;
  d->info_cnt = 1;
  strcpy (d->infos [0], fr->hytxt_frame_name);

  return 0;
}
