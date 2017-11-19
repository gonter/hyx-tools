/*
 *  FILE ~/usr/nl_kr/lib/nl_00107.c
 *
 *  scan in a word ref list together with the document info list
 *
 *  written:       1993-02-28
 *  latest update: 1995-07-22
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lmd_read_word_ref_list (
struct YTREE *yt,
void *client_data)
{
  struct WORD_REF *wr;
  struct LMDD_CONTROL *lmdd;
  FILE *f_wr;
  FILE *f_di;
  long doc_items_read;

  if (yt == (struct YTREE *) 0
      || (lmdd= (struct LMDD_CONTROL *) client_data)
           == (struct LMDD_CONTROL *) 0
      || (f_wr= lmdd->LMDD_fo_wr) == (FILE *) 0
      || (f_di= lmdd->LMDD_fo_di) == (FILE *) 0)
    return -1;

#ifdef DEBUG
printf ("nl_00107.c:\n");
#endif

  if ((wr= lmd_new_word_ref ()) == (struct WORD_REF *) 0) return -1L;

  if (lmd_find_word_ref (f_wr, yt->YT_info, wr) == 0)
  {
#ifdef DEBUG
printf ("nl_00107.c: word_ref gefunden, reading docinfo list\n");
#endif

    yt->YT_info= (long) wr;
    doc_items_read= lmd_read_document_info_list (f_di,
                        &wr->WR_ytree,
                        wr->WR_docinfo_offset,
                        wr->WR_docinfo_count);

    lmdd->LMDD_doc_items_written += doc_items_read;
  }

  return 0;
}
