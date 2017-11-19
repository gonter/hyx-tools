/*
 *  FILE %ned/07/ned0759.c
 *
 *  copy block
 *
 *  written:       1996-03-06
 *  latest update: 1997-10-26 10:49:40
 *  $Id: ned0759.c,v 1.2 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

extern int oper_level;
extern struct MARKER b_beg, b_end;

/* ------------------------------------------------------------------------ */
int ned_markup_block (
struct WINDOWCTRL *w,
int start_tag_segments,
const char *start_tag [],
int stop_tag_segments,
const char *stop_tag [])
{
  if (oper_level >= LEV_BLK
      || (w->WC_edit_mode & EDIT_READ_ONLY)
      || ned_blk_invalid ()
      || w->file_type == FTY_FTRWDW
     ) return -1;

  ned_feature_set (w, b_beg.ptr, b_beg.offset, Ftype_SGML_TAG,
                   start_tag_segments, start_tag);

  ned_feature_set (w, b_end.ptr, b_end.offset, Ftype_SGML_TAG,
                   stop_tag_segments, stop_tag);

  ned_display_window (w);

  return 0;
}
