/*
 *  FILE %ds/hytxt/hytxt020.c
 *
 *  create a list of frame segments by scanning a file
 *
 *  notes:
 *  - frame name and file name are strdup'ed, if they're specified
 *
 *  written:       1994-06-04
 *  latest update: 1996-10-13 16:04:34
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/hytxt.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
struct FILE_SEGMENT *hyx_make_segment (
struct FILE_SEGMENT **fs_app,
char *fn,                       /* contents source file name                */
char *frame_name,               /* selected frame name                      */
long *index_number,             /* index number chosen for the frame        */
int operation,
long fs_from,
long fs_size)
{
  struct FILE_SEGMENT *fs= (struct FILE_SEGMENT *) 0;
  struct HYTXT_FRAME *fd= (struct HYTXT_FRAME *) 0;
  struct HYTXT_FRAME *fd2;
  long index_nmbr;
  int rc;

  index_nmbr= (index_number == (long *) 0) ? 0L : *index_number;

  if (frame_name == (char *) 0)
  {
printf ("hyx_make_segment: fn='%s'\n", fn);
    rc= hytxt_scan (fn, &fd, HYXSM_hide_earlier|HYXSM_no_attributes);
printf ("rc=%d\n", rc);

    if (rc >= 0)
    {
      while ((fd2= fd) != (struct HYTXT_FRAME *) 0)
      {
        if ((fs= hyx_new_file_segment ()) == (struct FILE_SEGMENT *) 0)
        {
ERR:
          fprintf (stderr, "hyx_make_segment: no memory!\n");
          return (struct FILE_SEGMENT *) 0;
        }

        fs->FS_frame_name= fd->hytxt_frame_name;
        fs->FS_file_name= strdup (fn);
        fs->FS_from= fd->hytxt_frame_pos_beg;
        fs->FS_size= fd->hytxt_frame_pos_end - fd->hytxt_frame_pos_beg + 1L;
        fs->FS_operation= operation;
        if (index_nmbr > 0L) fs->FS_index= index_nmbr++;

        *fs_app= fs;
        fs_app= &fs->FS_next;

        fd->hytxt_frame_name= (char *) 0;       /* dont free! frame name    */
                                                /* gets reused              */
        fd= fd->hytxt_frame_next;
        free_HYTXT_FRAME (fd2);
      }
    }
  }
  else
  {
    if ((fs= hyx_new_file_segment ()) == (struct FILE_SEGMENT *) 0) goto ERR;

    if ((fs->FS_frame_name= hyx_translate_special_frame (frame_name))
         == (char *) 0)
      fs->FS_frame_name= strdup (frame_name);

    fs->FS_operation= operation;
    if (fn != (char *) 0) fs->FS_file_name= strdup (fn);
    if (index_nmbr > 0L) fs->FS_index= index_nmbr++;

    fs->FS_from= fs_from;
    fs->FS_size= fs_size;
    *fs_app= fs;
  }

  if (index_number != (long *) 0) *index_number= index_nmbr;

  return fs;
}
