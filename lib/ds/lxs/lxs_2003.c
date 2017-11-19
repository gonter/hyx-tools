/*
 *  FILE %ds/lxs/lxs_2003.c
 *
 *  dump a complete lexicon context
 *
 *  written:       1996-12-22
 *  latest update: 1996-12-22 11:52:25
 *
 */

#include <stdio.h>
#include <gg/lxs2.h>

/* ------------------------------------------------------------------------ */
int lxs_dump_context (struct LEXICON_CONTEXT *lxc, FILE *fo)
{
  if (lxc == (struct LEXICON_CONTEXT *) 0) return -1;

  fprintf (fo, "\nLexicon Context Name: %s (%s)\n",
           lxc->name, (lxc->to_lower) ? "lower" : "mixed");

  fprintf (fo, "BEGIN lower case dictionary\n");
  ytree_process_info (lxc->lower_case, lxs_dump_entry2, (void *) fo);
  fprintf (fo, "END lower case dictionary\n");

  fprintf (fo, "BEGIN mixed case dictionary\n");
  ytree_process_info (lxc->mixed_case, lxs_dump_entry2, (void *) fo);
  fprintf (fo, "END mixed case dictionary\n");

  return 0;
}
