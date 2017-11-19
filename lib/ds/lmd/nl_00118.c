/*
 *  FILE %nl_kr/lib/nl_00118.c
 *
 *  print a document hit list
 *
 *  written:       1993-02-28
 *  latest update: 1995-12-05
 *  $Id: nl_00118.c,v 1.4 2002/02/04 08:13:08 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_document_info_list_stdout (struct DOCUMENT_INFO_LIST *start)
{
  return lmd_print_document_info_list (stdout, start);
}

/* ------------------------------------------------------------------------ */
int lmd_print_document_info_list (
FILE *fo,
struct DOCUMENT_INFO_LIST *start)
{
  struct DOCUMENT_INFO *di;

  fprintf (fo, "rem:  hits   doc_id");

#ifdef LMD_EXTENDED_MODEL
  {
    int i;
    fprintf (fo, "    doc_ptr");
    for (i= 0; i < MAX_DI_POS; i++) fprintf (fo, "   position");
  }
#endif /* LMD_EXTENDED_MODEL */

  fputc ('\n', fo);

  for (; start != (struct DOCUMENT_INFO_LIST *) 0; start= start->DIL_next)
  {
    if ((di= start->DIL) == (struct DOCUMENT_INFO *) 0) continue;
/**********
fprintf (fo, ">>> dil=0x%08LX di=0x%08lX next=%08lX\n",
start, di, start->DIL_next);
*********/

    fprintf (fo, "hit: %5ld %8ld", di->DI_hit_count, di->DI_document_id);

#ifdef LMD_EXTENDED_MODEL
    {
      int i;

      fprintf (fo, " 0x%08lX", di->DI_document_ptr);
      for (i= 0; i < MAX_DI_POS; i++)
        fprintf (fo, " 0x%08lX", di->DI_pos [i]);
    }
#endif /* LMD_EXTENDED_MODEL */

    fputc ('\n', fo);
  }

  return 0;
}
