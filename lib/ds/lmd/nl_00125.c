/*
 *  FILE %ds/lmd/nl_00125.c
 *
 *  dump a word ref record
 *
 *  written:       1994-08-03
 *  latest update: 1995-12-26
 *
 */

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
long lmd_write_word_ref (
FILE *fo_word_ref,
struct WORD_REF *wr,
long doc_items_offset,
long doc_items_written)
{
  if (fo_word_ref == (FILE *) 0 || wr == (struct WORD_REF *) 0) return -1;

  dpp_fwrite_long (fo_word_ref, wr->WR_count, 4);

  /* CLEANUP: these variables are only used temporarily */
  dpp_fwrite_long (fo_word_ref, doc_items_offset, 4);
  dpp_fwrite_long (fo_word_ref, doc_items_written, 4);

  return 0;
}
