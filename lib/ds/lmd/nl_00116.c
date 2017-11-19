/*
 *  FILE %ds/lmd/nl_00116.c
 *
 *  print word reference information
 *
 *  written:       1994-07-31
 *  latest update: 1995-12-26
 *  $Id: nl_00116.c,v 1.2 2001/08/26 23:26:02 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_word_ref_info (FILE *fo, struct WORD_REF *wr)
{
  if (fo == (FILE *) 0 || wr == (struct WORD_REF *) 0) return -1;

  fprintf (fo,
           "count: %ld\n",
           wr->WR_count);

  /* CLEANUP: these variables are only used temporarily */
  fprintf (fo,
           "doc_offset: 0x%08lX\ncnt: %ld\n",
           wr->WR_docinfo_offset,
           wr->WR_docinfo_count);

  return 0;
}
