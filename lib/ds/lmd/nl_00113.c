/*
 *  FILE %nl_kr/lib/nl_00113.c
 *
 *  print a document hit list as gopher index
 *
 *  written:       1993-03-07
 *  latest update: 1995-12-05
 *  $Id: nl_00113.c,v 1.3 2001/09/10 06:58:38 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/hyx.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCDIR_LIST *lmd_read_docdir_info (
char *document_dir,
struct WORD_REF_LIST *wrl)
{
  struct DOCDIR_LIST *dl1= (void *) 0;
  struct DOCDIR_LIST *dl2;
  struct DOCDIR_LIST **dlapp;
  FILE *fi;
  int rc;
  long docid;
  char *line1= (char *) 0;
  char *line2= (char *) 0;
#define MAX_LINE 2048

  if (document_dir == (char *) 0
      || *document_dir == 0
      || (line1= malloc (MAX_LINE)) == (char *) 0
      || (line2= malloc (MAX_LINE)) == (char *) 0
      || (fi= fopen (document_dir, "r")) == (FILE *) 0
     ) goto END;

  dlapp= &dl1;

  for (;;)
  {
NEXT:
    rc= fread_line (fi, line1, MAX_LINE);
    if (rc < 0 && feof (fi)) break;
    if (rc == 0) continue;

    if (find_attr_value (line1, line2, MAX_LINE, "docid") != 0) goto NEXT;
    docid= get_parameter_value (line2);

    if ((dl2= lmd_get_docdir_info (line1, line2, MAX_LINE, docid, wrl))
        != (void *) 0)
    {
      *dlapp= dl2;
      dlapp= &dl2->DL_next;
    }
  }

  fclose (fi);

END:
  free_or_what (line1);
  free_or_what (line2);

  return dl1;
}
