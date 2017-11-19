/*
 *  FILE %nl_kr/lib/nl_00109.c
 *
 *  read a document info list
 *
 *  written:       1993-02-28
 *  latest update: 1995-12-06
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>
#include <gg/dpp.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
long lmd_read_document_info_list (
FILE *fi,
struct YTREE **wrl_ytree,
long offset,
long cnt)
{
  struct DOCUMENT_INFO *di;
  long items_read= 0L;
  char docid_str [10];
  long doc_id;
  long hit_count;
  long pos;

  pos= (sizeof (struct DOCUMENT_INFO)) * offset;
  fseek (fi, pos, 0);

#ifdef DEBUG
printf ("nl_00109: read doc info: offset=%ld pos=0x%08lX\n", offset, pos);
#endif

  for (; cnt > 0L; cnt--)
  {
    for (;;)
    {
      doc_id=    dpp_fread_long (fi, 4);
      hit_count= dpp_fread_long (fi, 4);

      if (feof (fi)) return -1;
      if (doc_id != 0xFFFFFFFE) break;

      /* partial dump continuation entry */
      fseek (fi, hit_count, 0);
    }

    if ((di= lmd_new_document_info ()) == (struct DOCUMENT_INFO *) 0)
      return -1;

    long_to_hex (doc_id, docid_str);
#ifdef DEBUG
printf ("nl_00109: doc_id=0x%08lX -> %s (%ld)\n", doc_id, docid_str, doc_id);
#endif

    di->DI_document_id= doc_id;
    di->DI_hit_count=   hit_count;

#ifdef LMD_EXTENDED_MODEL
    {
      int i;
      long doc_ptr;

      doc_ptr= dpp_fread_long (fi, 4);
      di->DI_document_ptr= doc_ptr;
      for (i= 0; i < MAX_DI_POS; i++)
        di->DI_pos [i]= dpp_fread_long (fi, 4);
    }
#endif /* LMD_EXTENDED_MODEL */

    /* SORT_DOCID: sortieren nach document_id */
    lmd_docid_list_insert (di, wrl_ytree, docid_str);

    items_read++;
  }

  return items_read;
}
