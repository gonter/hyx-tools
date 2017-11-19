/*
 *  FILE ~/usr/ned/08/ned0848.c
 *
 *  retrieve frame begin and end offsets from the index table
 *
 *  written:       1991 05 29
 *  latest update: 1994-03-16
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
int get_index (struct FRAMECTRL *fr)
{
  FILE *fidx;

  if (fr == (struct FRAMECTRL *) 0
     || fr->cluster == (struct CLUSTERCTRL *) 0
     || (fidx= fopen (fr->cluster->cluster_name_idx, "rb")) == (FILE *) 0)
    return -1;

  fseek (fidx, fr->frame_index * IDX_REC_SIZE, 0);
  fr->frame_begin = dpp_fread_long (fidx, 4);
  fr->frame_end   = dpp_fread_long (fidx, 4);
  fclose (fidx);

  return 0;
}
