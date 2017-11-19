/*
 *  FILE ~/usr/nl_kr/lib/nl_00123.c
 *
 *  print a document hit list as gopher index
 *
 *  written:       1993-03-07
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_gopher_hit_list (
FILE *fo,
char *document_dir,
struct WORD_REF_LIST *wrl,
char *path_prefix,
char *item_type,
char *host_name,
long port_number)
{
  struct DOCDIR_LIST *dl1;
  int lines= 0;

  if (wrl == (struct WORD_REF_LIST *) 0
     || (dl1= lmd_read_docdir_info (document_dir, wrl))
         == (struct DOCDIR_LIST *) 0) return -1;

  lines= lmd_print_docdir_gopher (fo, dl1, path_prefix, item_type,
                       host_name, port_number);
  lmd_free_docdir_list (dl1);

  return lines;
}
