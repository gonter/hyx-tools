/*
 *  FILE %ds/lmd/nl_00504.c
 *
 *  delete all references to a certain document from the
 *  complete word tree
 *
 *  written:       1993-02-28
 *                 1994-12-18: isolated from  wordcr05.c
 *  latest update: 1995-07-22
 *  $Id: nl_00504.c,v 1.2 2001/08/26 23:26:03 gonter Exp $
 *
 */

#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_discard_document_id (
struct LMDC_CONTROL *lmdc,
long doc_id)
{
  ytree_process (lmdc->LMDC_ytree, lmd_discard_doc_id, (void *) doc_id);

  return 0;
}
