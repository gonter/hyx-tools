/*
 *  FILE %ds/hytxt/hytxt034.c
 *
 *  written:       1996-07-09
 *  latest update: 1996-10-09 21:31:18
 *
 */

#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_setup_delete_segment (
struct FILE_SEGMENT **app_segments,
struct FILE_SEGMENT **fs_new,
char *frame_name,
long *index_number)
{
  struct FILE_SEGMENT *fs;

  if (frame_name == (char *) 0) return -1;

  if ((fs= hyx_make_segment (app_segments, (char *) 0, frame_name,
             index_number, FSop_delete, 0L, 0L))
      == (struct FILE_SEGMENT *) 0) return -1;

  *fs_new= fs;

  return 0;
}
