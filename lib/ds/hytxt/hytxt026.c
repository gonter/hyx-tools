/*
 *  FILE %ds/hytxt/hytxt026.c
 *
 *  seek a frame by name
 *
 *  see also: hyx_seek_by_index ()
 *            hcc_seek_by_name ()
 *
 *  written:       1993-12-26
 *  latest update: 1996-03-24 18:46:41
 *  $Id: hytxt026.c,v 1.2 2002/01/27 23:01:40 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/strings.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
long hyx_seek_by_name (
FILE *fi_hyx,
FILE *fi_idx,
FILE *fi_lut,
FILE *fi_xfn,
char *frame_name)
{
  long size= -1L;
  long idx;
  char *alt_name= (char *) 0;

  if ((alt_name= hyx_translate_special_frame (frame_name)) != (char *) 0)
    frame_name= alt_name;

  if ((idx= hyx_get_index (fi_idx, fi_lut, fi_xfn, frame_name)) > 0L)
     size= hyx_seek_by_index (fi_hyx, fi_idx, idx);

  free_or_what (alt_name);
  return size;
}
