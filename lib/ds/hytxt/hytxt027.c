/*
 *  FILE ~/usr/sgml/hytxt027.c
 *
 *  written:       1994-11-30
 *  latest update: 1995-07-09
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_print_segment (
FILE *fo,
struct FILE_SEGMENT *fs)
{
  char *last_file_name= (char *) 0;
  char *fs_fnm;

  for (; fs != (struct FILE_SEGMENT *) 0; fs= fs->FS_next)
  {
    if ((fs_fnm= fs->FS_file_name) != (char *) 0
       && (last_file_name == (char *) 0
           || (last_file_name != (char *) 0
               && strcmp (last_file_name, fs_fnm) != 0)))
      fprintf (fo, "FILE %s\n", fs_fnm);

    last_file_name= fs_fnm;

    fprintf (fo, "0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%08lX 0x%08lX %c",
             fs->FS_index, fs->FS_begin, fs->FS_end, fs->FS_cluster,
             fs->FS_from, fs->FS_size, fs->FS_operation);

    if ((fs_fnm= fs->FS_frame_name) != (char *) 0)
      fprintf (fo, " %s", fs_fnm);

    fputc ('\n', fo);
  }

  return 0;
}
