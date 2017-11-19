/*
 *  FILE ~/usr/nl_kr/lib/nl_00114.c
 *
 *  print a document hit list as gopher index
 *
 *  written:       1994-08-01: isolated from nl_00110.c
 *  latest update: 1995-07-22
 *
 */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/hyx.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCDIR_LIST *lmd_get_docdir_info (
char *line1,
char *line2,
int MAX_LINE,
long docid,
struct WORD_REF_LIST *wrl)
{
  struct DOCUMENT_INFO_LIST *start;
  struct DOCDIR_LIST *dl1= (struct DOCDIR_LIST *) 0;
  struct DOCDIR_LIST *dl2;
  struct DOCDIR_LIST **dlapp;

  dlapp= &dl1;

  for (; wrl != (struct WORD_REF_LIST *) 0; wrl= wrl->WRL_next)
    for (start= wrl->WRL_dil;
         start != (struct DOCUMENT_INFO_LIST *) 0;
         start= start->DIL_next)
      if (start->DIL->DI_document_id == docid)
      {
        if (find_attr_value (line1, line2, MAX_LINE, "name") != 0)
          return (struct DOCDIR_LIST *) 0;

        dl2= (struct DOCDIR_LIST *) calloc (sizeof (struct DOCDIR_LIST), 1);
        dl2->DL_di= start->DIL;

        dl2->DL_name= strdup (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "path") == 0)
          dl2->DL_path= strdup (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "file") == 0)
          dl2->DL_file= strdup (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "from") == 0)
          dl2->DL_from= get_parameter_value (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "to") == 0)
          dl2->DL_to= get_parameter_value (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "size") == 0)
          dl2->DL_size= get_parameter_value (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "lfrom") == 0)
          dl2->DL_lfrom= get_parameter_value (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "lto") == 0)
          dl2->DL_lto= get_parameter_value (line2);

        if (find_attr_value (line1, line2, MAX_LINE, "lines") == 0)
          dl2->DL_lines= get_parameter_value (line2);

        *dlapp= dl2;

         dlapp= &dl2->DL_next;
        break; /* ???? */
      }

  free (line2);

  return dl1;
}
