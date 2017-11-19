/*
 *  FILE %ds/lmd/nl_00514.c
 *
 *  delete all document info pointers in the document tree
 *  associated with a WORD_REF structure if document id matches
 *  or is 0L.  
 *
 *  written:       1995-07-19
 *  latest update: 2001-02-04 20:36:43
 *  $Id: nl_00514.c,v 1.4 2001/09/10 06:58:41 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_discard_document_node (struct YTREE *yt, void *cd)
{
  struct DOCUMENT_INFO *di;
  long doc_id;

  doc_id= (long) cd;

  if (yt != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW)
      && (di= (struct DOCUMENT_INFO *) yt->YT_info)
          != (struct DOCUMENT_INFO *) 0
      && (doc_id <= 0L || doc_id == di->DI_document_id)  /* ????? */
     )
  {
    free (di);
    yt->YT_info= 0L;
  }

  return 0;
}
