/*
 *  FILE ~/usr/nl_kr/lib/nl_00511.c
 *
 *  manipulate word information data structures
 *
 *  written:       1995-07-18
 *  latest update: 1995-07-18
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_lmdd (FILE *fo, struct LMDD_CONTROL *lmdd)
{
  fprintf (fo, "word_index=%ld doc_offset=%ld items_written= %ld\n",
    lmdd->LMDD_word_index, lmdd->LMDD_doc_items_offset,
    lmdd->LMDD_items_written);

  return 0;
}
