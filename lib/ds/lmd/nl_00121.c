/*
 *  FILE %nl_kr/lib/nl_00121.c
 *
 *  print a document hit list as hypertext link page
 *
 *  written:       1993-03-07
 *  latest update: 1995-12-05
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_hyx_hit_list (
FILE *fo,
char *document_dir,
struct WORD_REF_LIST *wrl)
{
  struct DOCDIR_LIST *dl1= (struct DOCDIR_LIST *) 0;

  if (wrl == (struct WORD_REF_LIST *) 0) return -1;

  if ((dl1= lmd_read_docdir_info (document_dir, wrl))
      != (struct DOCDIR_LIST *) 0)
  {
    lmd_print_docdir_hyx (fo, dl1);
    lmd_free_docdir_list (dl1);
  }
  else
  {
    lmd_print_hyx_cluster_hit_list (fo, wrl, (char *) 0);
  }

  return 0;
}
