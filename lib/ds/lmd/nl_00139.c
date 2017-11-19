/*
 *  FILE %nl_kr/lib/nl_00139.c
 *
 *  print a document hit list
 *
 *  written:       1993-02-28
 *  latest update: 1995-12-05
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_hyx_cluster_hit_list (
FILE *fo,
struct WORD_REF_LIST *wrl,
char *cluster_name)
{
  struct DOCUMENT_INFO_LIST *start;
  struct DOCUMENT_INFO *di;

  if (cluster_name != (char *) 0 && *cluster_name == 0)
    cluster_name= (char *) 0;

  for (; wrl != (struct WORD_REF_LIST *) 0; wrl= wrl->WRL_next)
  {
    fprintf (fo, "\n--------------------\n");
    fprintf (fo, "word: %s\n", wrl->WRL_string);
    lmd_print_word_ref_info (fo, &wrl->WRL);

    fprintf (fo, "frnum hits\n");
    if ((start= wrl->WRL_dil) != (struct DOCUMENT_INFO_LIST *) 0)
    {
      for (start= wrl->WRL_dil;
           start != (struct DOCUMENT_INFO_LIST *) 0; 
           start= start->DIL_next)
      {
        if ((di= start->DIL) == (struct DOCUMENT_INFO *) 0) continue;

        fprintf (fo, "<hyx.l fr=\"$#%ld\"", di->DI_document_id);
        if (cluster_name != (char *) 0)
          fprintf (fo, " cl=\"%s\"", cluster_name);
        fprintf (fo, " tdc=hyx.l tdp=5>%5ld %5ld\n",
                 di->DI_document_id, di->DI_hit_count);
      }
    }
  }

  return 0;
}
