/*
 *  FILE ~/usr/sgml/hytxt021.c
 *
 *  destroy a list of frame segments (just the data structures)
 *
 *  written:       1994-06-19
 *  latest update: 1995-07-09
 *
 */

#include <stdlib.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_destroy_segments (struct FILE_SEGMENT *fs)
{
  struct FILE_SEGMENT *fs2;

  while (fs != (struct FILE_SEGMENT *) 0)
  {
    fs2= fs->FS_next;
    if (fs->FS_frame_name != (char *) 0) free (fs->FS_frame_name);
    if (fs->FS_file_name  != (char *) 0) free (fs->FS_file_name);
    free (fs);
    fs= fs2;
  }

  return 0;
}
