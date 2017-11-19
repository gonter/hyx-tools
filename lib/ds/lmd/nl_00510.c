/*
 *  FILE %nl_kr/lib/nl_00510.c
 *
 *  write word info attached to a ytree node into their files
 *  used while dumping the complete ytree in lmd_write_tables()
 *
 *  written:       1995-07-18
 *  latest update: 1995-12-06
 *  $Id: nl_00510.c,v 1.3 2001/08/26 23:26:03 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_dump_word_entry (struct YTREE *yt, void *client_data)
{
  struct LMDD_CONTROL *lmdd;
  struct WORD_REF *wr;
  struct YTREE *doc_infos;
  long doc_items_written;

  if (yt == (struct YTREE *) 0
      || (lmdd= (struct LMDD_CONTROL *) client_data)
          == (struct LMDD_CONTROL *) 0
     )
    return -1;

  if ((wr= (struct WORD_REF *) yt->YT_info) != (struct WORD_REF *) 0)
  {
    doc_infos= wr->WR_ytree;

    if (lmdd->LMDD_mode == LMDD_mode_partial
        && doc_infos != (struct YTREE *) 0 /* is this possible? */
        && doc_infos->YT_next == (struct YTREE *) 0
        && doc_infos->YT_down == (struct YTREE *) 0
       ) /* only one entry, nothing to do in partial mode ... */
      return 0;

    lmdd->LMDD_doc_items_written= 0L;
    ytree_process (doc_infos, lmd_dump_document_info_list, lmdd);
    doc_items_written= lmdd->LMDD_doc_items_written;

    if (lmdd->LMDD_mode == LMDD_mode_partial)
    { /* create the chaining entry after a partial dump */
      struct DOCUMENT_INFO *di;

      ytree_free (doc_infos);
      wr->WR_ytree= (struct YTREE *) 0;
      if ((di= lmd_insert_document_info (wr, 0xFFFFFFFE,
                 "FFFFFFFE" /* this smells buggy, see nl_00601.c */))
          != (struct DOCUMENT_INFO *) 0)
        di->DI_hit_count= lmdd->LMDD_doc_items_offset;
    }
    else
    {
      lmd_write_word_ref (lmdd->LMDD_fo_wr, wr,
                          lmdd->LMDD_doc_items_offset,
                          doc_items_written);

      yt->YT_info= lmdd->LMDD_word_index++;
    }

    lmdd->LMDD_doc_items_offset += doc_items_written;
    lmdd->LMDD_items_written++;
  }

  return 0;
}
