/*
 *  FILE ~/usr/sgml/hytxt023.c
 *
 *  written:       1994-07-17
 *  latest update: 1994-07-17
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
static struct HYTXT_FRAME frame;
static char frame_name [1024];

/* ------------------------------------------------------------------------ */
int hytxt_scan_file (FILE *fo, char *fn)
{
  FILE *hyx;                    /* HYX file currently scanned               */
  long hyx_pos= 0L;             /* position of frame beginning in file      */
  long act_length;              /* length of the scanned frame              */
  long act_index;               /* the number of the frame within the       */
                                /* cluster without taking note of           */
                                /* duplicated frames                        */
  int rc;                       /* return code from frame scanning          */
  char md5_str [34];            /* MD5 checksum for the given frame         */

  if ((hyx= fopen (fn, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "File %s not opened!\n", fn);
    return -2;
  }

  frame.hytxt_frame_name= frame_name;

  for (act_index= 1L;; act_index++)
  {
    rc= hytxt_scan_entry (hyx, &hyx_pos, &frame,
                          HYXSM_no_attributes|HYXSM_no_allocation,
                          md5_str);
    if (rc != 0) break;

    act_length= frame.hytxt_frame_pos_end - frame.hytxt_frame_pos_beg + 1L;
    fprintf (fo, "0x%08lX 0x%08lX 0x%08lX %s %s\n",
             act_index, frame.hytxt_frame_pos_beg,
             act_length, md5_str, frame_name);
  }

  fclose (hyx);

  return 0;
}
