/*
 *  FILE %lexicon/dict0005.c
 *
 *  written:       1994-12-10: isolated from dictadd1.c
 *  latest update: 1997-11-01 11:58:05
 *
 */

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/hytxt.h>
#include <gg/parse.h>

/* statistics: ------------------------------------------------------------ */
extern long YTREE_ALLOCATED;
extern long YTREE_ALLOC_SIZE;

/* ------------------------------------------------------------------------ */
int dict_add_finish (
struct HYX_CLUSTER_CONTROL *hcc,
struct LEXICON_CONTROL *lcc)
{
  long unique;

  if (!hcc->HCC_dictadd1_inited) return 0;

  if (hcc->HCC_dict_mode == DAMODE_MERGE
      || hcc->HCC_dict_mode == DAMODE_LOOKUP
      || hcc->HCC_dict_mode == DAMODE_REPLACE
     )
  {
    dict_flush_queue (hcc, lcc);

    unique= hcc_update_index (hcc,
                              ytree_entry_descriptor_to_index,
                              dict_write_xfn_entry);

    printf ("LUT file %s: \n", hcc->HCC_fnm_lut);
    printf ("%ld nodes; %ld byte; %ld unique entries\n",
            YTREE_ALLOCATED, YTREE_ALLOC_SIZE, unique);
  }

  return 0;
}
