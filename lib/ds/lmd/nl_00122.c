/*
 *  FILE %nl_kr/lib/nl_00122.c
 *
 *  print a document hit list as hypertext link page
 *
 *  written:       1994-08-01
 *  latest update: 1995-12-05
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_docdir_hyx (FILE *fo, struct DOCDIR_LIST *docdir)
{
  fprintf (fo, "  (hits) name\n------------------\n");

  for (; docdir != (struct DOCDIR_LIST *) 0;)
  {
    fprintf (fo,
             "<hyx.l file=\"%s\">* (%4ld) %s\n",
             docdir->DL_file,
             docdir->DL_di->DI_hit_count,
             docdir->DL_name);
  }

  return 0;
}
