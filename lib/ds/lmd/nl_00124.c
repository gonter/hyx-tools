/*
 *  FILE ~/usr/nl_kr/lib/nl_00124.c
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
int lmd_print_docdir_gopher (
FILE *fo,
struct DOCDIR_LIST *dl2,
char *path_prefix,
char *item_type,
char *host_name,
long port_number)
{
  int lines= 0;

  while (dl2 != (struct DOCDIR_LIST *) 0)
  {
    fprintf (fo, "%s[%ld] %s\t",
             item_type,
             dl2->DL_di->DI_hit_count,
             dl2->DL_name);

    if (dl2->DL_path != (char *) 0)
    { /* use predefined gopher path string */
      fprintf (fo, "%s", dl2->DL_path);
    }
    else
    { /* generate a gopher path string */
      if (dl2->DL_from != 0L
         && (dl2->DL_to != 0L || dl2->DL_size != 0L))
      {
        fprintf (fo, "R%08ld-%08ld-",
          dl2->DL_from,
          (dl2->DL_to != 0L) ? dl2->DL_to : (dl2->DL_from + dl2->DL_size));
      }

      fprintf (fo, "%s%ld",
        path_prefix,
        dl2->DL_di->DI_document_id);

      if (dl2->DL_lfrom != 0L
         && (dl2->DL_lto != 0L || dl2->DL_lines != 0L))
      {
        fprintf (fo, ":%ld:%ld",
          dl2->DL_lfrom,
          (dl2->DL_lto != 0L) ? dl2->DL_lto : (dl2->DL_lfrom + dl2->DL_lines));
      }
    }

    fprintf (fo, "\t%s\t%ld\n", host_name, port_number);
    lines++;
  }

  return lines;
}
