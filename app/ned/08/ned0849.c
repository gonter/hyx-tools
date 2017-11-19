/*
 *  FILE ~/usr/ned/08/ned0849.c
 *
 *  update an index entry for a frame in the index table file
 *
 *  written:       1991 05 31
 *  latest update: 1994-03-31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/dpp.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int update_index (
struct CLUSTERCTRL *cl,
long idx,
long off_beg,
long off_end,
long cl_nr)
{
  FILE *fidx;
  long cnt;

  if (idx <= 0L) return -1;

  if (cl->highest_index > idx)
  { /* update for old index entry */
    if ((fidx= fopen (cl->cluster_name_idx, "r+b")) == (FILE *) 0) return -1;
    fseek (fidx, idx * IDX_REC_SIZE, 0);
  }
  else
  { /* append a new index entry */
    if ((fidx= fopen (cl->cluster_name_idx, "ab")) == (FILE *) 0) return -1;
    if ((cnt= idx - cl->highest_index) > 0L)
    { /* fille up space in table up to new index entry position */
      cl->highest_index= idx;
      for (cnt *= IDX_REC_SIZE; cnt > 0L; cnt--)
        fputc (0x00FF, fidx);
    }
    cl->highest_index++;
  }

  dpp_fwrite_long (fidx, off_beg, 4);
  dpp_fwrite_long (fidx, off_end, 4);
  dpp_fwrite_long (fidx, cl_nr,   4);

  fclose (fidx);

  return 0;
}
