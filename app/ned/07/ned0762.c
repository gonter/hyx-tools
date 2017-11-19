/*
 *  FILE %ned/07/ned0762.c
 *
 *  copy block
 *
 *  written:       1996-03-07
 *  latest update: 1997-10-26 10:48:52
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int block_mode;

/* ------------------------------------------------------------------------ */
int ned_set_tag (
struct WINDOWCTRL *w,
struct LINE *l,
int offset,
int start_tag_segments,
char *start_tag [],
int stop_tag_segments,
char *stop_tag [])
{
  if ((w->WC_edit_mode & EDIT_READ_ONLY) || w->file_type == FTY_FTRWDW)
    return -1;

  w->f_upd= 1;

  q_feature_set (l, offset, Ftype_SGML_TAG,
                 start_tag_segments, start_tag);

  ... T2D 1996-03-07  9:11:52
  ned_identify_feature (w, l, offset, Ftype_SGML_TAG, start_tag [0],
                      buffer1a, buffer1b, &repl_size, MAX_BUFFER1);

  return 0;
}
