/*
 *  FILE %ds/hytxt/hytxt033.c
 *
 *  written:       1995-06-25
 *  latest update: 1997-11-01 12:43:41
 *
 */

#include <stdio.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>

/* ------------------------------------------------------------------------ */
int hyx_update_index (
char *index_file,
long li_begin,
long li_end,
long li_cluster_number,
long *frame_index,
long *next_index)
{
  FILE *fidx;                   /* Index File                               */

  if (*frame_index < *next_index)
  { /* Update fuer alten Index */
    long position;              /* Filepointer Position innerhalb des       */
                                /* Index Files, bzw. des Lexicon Files      */

    if ((fidx= flopen (index_file, "r+b")) == (FILE *) 0) return -1;

    position= *frame_index * ((long) HYXIDX_REC_SIZE);
    fseek (fidx, position, 0);
    dpp_fwrite_long (fidx, li_begin,          4);
    dpp_fwrite_long (fidx, li_end,            4);
    dpp_fwrite_long (fidx, li_cluster_number, 4);
  }
  else
  {
    if ((fidx= flopen (index_file, "ab")) == (FILE *) 0) return -1;

    for (; *next_index < *frame_index; (*next_index)++)
    {
      dpp_fwrite_long (fidx, -1L, 4);
      dpp_fwrite_long (fidx, -1L, 4);
      dpp_fwrite_long (fidx, -1L, 4);
    }

    dpp_fwrite_long (fidx, li_begin,          4);
    dpp_fwrite_long (fidx, li_end,            4);
    dpp_fwrite_long (fidx, li_cluster_number, 4);
    (*next_index)++;
  }

  return 0;
}
