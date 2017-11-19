/*
 *  FILE ~/usr/nl_kr/lib/nl_00112.c
 *
 *  free a list of docdir records
 *
 *  written:       1993-03-07
 *  latest update: 1995-07-16
 *
 */

#include <stdlib.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_free_docdir_list (struct DOCDIR_LIST *dl1)
{
  struct DOCDIR_LIST *dl2;

  for (dl2= dl1; dl2 != (struct DOCDIR_LIST *) 0;)
  {
    dl1= dl2->DL_next;
    if (dl2->DL_name != (char *) 0) free (dl2->DL_name);
    if (dl2->DL_path != (char *) 0) free (dl2->DL_path);
    if (dl2->DL_file != (char *) 0) free (dl2->DL_file);
    free (dl2);
    dl2= dl1;
  }

  return 0;
}
