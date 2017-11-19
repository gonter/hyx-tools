/*
 *  FILE %ds/hytxt/hytxt036.c
 *
 *  setup a segment that a frame can be taken from stdin
 *
 *  written:       1996-10-09
 *  latest update: 1996-10-09 21:27:54
 *
 */

#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_setup_stdin_segment (
struct FILE_SEGMENT **app_segments,
struct FILE_SEGMENT **fs_new,
char *frame_name,
long *index_number)
{
  struct FILE_SEGMENT *fs;
  long f_beg;
  long f_siz;

  f_beg= 0L;
  f_siz= 0x7FFFFFFFL;

  if ((fs= hyx_make_segment (app_segments, "-", frame_name,
             index_number, FSop_update, f_beg, f_siz))
      == (struct FILE_SEGMENT *) 0) return -1;

  *fs_new= fs;

  return 0;
}
