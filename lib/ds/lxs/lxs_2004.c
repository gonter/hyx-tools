/*
 *  FILE %ds/lxs/lxs_2004.c
 *
 *  dump a single lexicon entry
 *
 *  written:       1996-12-22
 *  latest update: 1996-12-22 11:52:25
 *
 */

#include <stdio.h>
#include <gg/lxs2.h>

/* ------------------------------------------------------------------------ */
int lxs_dump_entry (struct LEXICON_ENTRY *lxe, FILE *fo)
{
  if (lxe == (struct LEXICON_ENTRY *) 0) return -1;

  fprintf (fo, "%7ld %s\n", lxe->ref_count, lxe->entry);

  return 0;
}

/* ------------------------------------------------------------------------ */
int lxs_dump_entry2 (long entry_ref, void *cd)
{
  return lxs_dump_entry ((struct LEXICON_ENTRY *) entry_ref,
                         (FILE *) cd);
}
