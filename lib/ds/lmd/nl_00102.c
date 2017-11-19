/*
 *  FILE %nl_kr/lib/nl_00102.c
 *
 *  dump a document info list
 *
 *  written:       1993-02-28
 *  latest update: 1995-12-05
 *  $Id: nl_00102.c,v 1.4 2001/09/10 06:58:37 gonter Exp $
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gg/lookup.h>
#include <gg/dpp.h>

/* ------------------------------------------------------------------------ */
int lmd_dump_document_info_list (struct YTREE *yt, void *client_data)
{
  struct LMDD_CONTROL *lmdd;
  struct DOCUMENT_INFO *di;
  FILE *fo;

  if (yt == (struct YTREE *) 0
      || (lmdd= (struct LMDD_CONTROL *) client_data)
          == (struct LMDD_CONTROL *) 0
      || (di= (struct DOCUMENT_INFO *) yt->YT_info)
          == (struct DOCUMENT_INFO *) 0
      || (fo= lmdd->LMDD_fo_di) == (FILE *) 0
     )
    return -1;

  dpp_fwrite_long (fo, di->DI_document_id, 4);
  dpp_fwrite_long (fo, di->DI_hit_count, 4);

#ifdef LMD_EXTENDED_MODEL
  {
    int i;

    dpp_fwrite_long (fo, di->DI_document_ptr, 4);
    for (i= 0; i < MAX_DI_POS; i++)
      dpp_fwrite_long (fo, di->DI_pos [i], 4);
  }
#endif /* LMD_EXTENDED_MODEL */

  /* release no longer needed data */
  free (di);
  yt->YT_info= (long) 0;

  lmdd->LMDD_doc_items_written++;

  return 0;
}
