/*
 *  FILE %ds/lmd/nl_00104.c
 *
 *  deref a word
 *
 *  written:       1993-02-28
 *  latest update: 1995-07-31
 *  $Id: nl_00104.c,v 1.4 2002/01/29 08:01:41 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct WORD_REF_LIST *lmd_deref_word (
struct LMD_QUERY_SET *lmdqs,
char *w,
int exact)
{
  struct WORD_REF_LIST *wrl= (struct WORD_REF_LIST *) 0;
  struct WORD_REF_LIST *xwrl;
  struct DEREF_CONTROL dc;
  int rc;

#ifdef DEBUG
printf ("nl_00104: w='%s' exact=%d init=%d\n", w, exact, lmdqs->LMDQS_initialized);
#endif /* DEBUG */

  if (!lmdqs->LMDQS_initialized
     ||(rc= lmd_deref_word_ref (lmdqs, w, exact, &wrl)) != 0)
    return (struct WORD_REF_LIST *) 0;

#ifdef DEBUG
printf ("nl_00104: reading di list\n");
#endif /* DEBUG */

  for (xwrl= wrl; xwrl != (struct WORD_REF_LIST *) 0; xwrl= xwrl->WRL_next)
  {
    lmd_read_document_info_list (lmdqs->LMDQS_F_di,
                                 &xwrl->WRL.WR_ytree,
                                 xwrl->WRL.WR_docinfo_offset,
                                 xwrl->WRL.WR_docinfo_count);

    dc.DC_dil= (struct DOCUMENT_INFO_LIST *) 0;
    dc.DC_dil_app= &dc.DC_dil;
    ytree_process (xwrl->WRL.WR_ytree, lmd_create_dil, (void *) &dc);
    xwrl->WRL_dil= dc.DC_dil;
  }

  return wrl;
}
