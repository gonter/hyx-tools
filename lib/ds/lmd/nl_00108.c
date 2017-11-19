/*
 *  FILE %ds/lmd/nl_00108.c
 *
 *  scan in a word ref item
 *
 *  written:       1994-02-21
 *  latest update: 1995-07-30
 *  $Id: nl_00108.c,v 1.3 2002/12/24 07:00:51 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lmd_read_word_ref (FILE *fi_word_ref, struct WORD_REF *wr)
{
#ifdef DEBUG
printf ("nl_00108:\n");
#endif /* DEBUG */

  if (wr == (struct WORD_REF *) 0) return -1;

  wr->WR_count=            dpp_fread_long (fi_word_ref, 4);

  /* CLEANUP: these variables are only used temporarily */
  wr->WR_docinfo_offset=   dpp_fread_long (fi_word_ref, 4);
  wr->WR_docinfo_count=    dpp_fread_long (fi_word_ref, 4);

#ifdef DEBUG
printf ("nl_00108: cnt=%ld doc_off=0x%08lX doc_cnt=%ld\n",
wr->WR_count, wr->WR_docinfo_offset, wr->WR_docinfo_count);
#endif /* DEBUG */

  if (feof (fi_word_ref)) return 0;

  return 1;
}
