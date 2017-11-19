/*
 *  FILE ~/usr/sgml/msrv03.c
 *
 *  written:       1994-06-19
 *  latest update: 1999-04-24 12:00:41
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include "msrvh.h"

/* ------------------------------------------------------------------------ */
static char line [LINE_SIZE];

/* ------------------------------------------------------------------------ */
struct MSRV_defaults *msrv_get_defaults (char *fnm)
{
  FILE *fi;
  struct MSRV_defaults *msrv_def;
  struct MSRV_authorization *msrv_auth;
#define N_FIELDS 5
  char *fields [N_FIELDS];
  char *kw;
  int n_fields;
  int rc;

  if ((msrv_def= (struct MSRV_defaults *)
                 calloc (sizeof (struct MSRV_defaults), 1))
      == (struct MSRV_defaults *) 0)
  {
    fprintf (stderr, "msrv_get_defaults: can't allocate memory\n");
    return (struct MSRV_defaults *) 0;
  }

  if ((fi= fopen (fnm, "r")) == (FILE *) 0)
  {
    fprintf (stderr, "msrv_get_defaults: can't read %s\n", fnm);
    return (struct MSRV_defaults *) 0;
  }

  for (;;)
  {
    rc= fread_line (fi, line, LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;

    if (line [0] == '#') continue;
    n_fields= split_string (line, '|', fields, N_FIELDS);
    if (n_fields == 0) continue;

    kw= fields[0];
    to_lower (kw);

    if (strcmp (kw, "database") == 0)
    {
      str_assign (&msrv_def->MD_database, fields[1]);
    }
    else
    if (strcmp (kw, "sender") == 0)
    {
      str_assign (&msrv_def->MD_sender, fields[1]);
    }
    else
    if (strcmp (kw, "errors-to") == 0)
    {
      str_assign (&msrv_def->MD_errors_to, fields[1]);
    }
    else
    if (strcmp (kw, "cc") == 0)
    {
      str_assign (&msrv_def->MD_cc, fields[1]);
    }
    else
    if (strcmp (kw, "name") == 0)
    {
      str_assign (&msrv_def->MD_name, fields[1]);
    }
    else
    if (strcmp (kw, "authorize") == 0)
    {
      msrv_auth= msrv_make_authorization (fields[1], fields[2]);
      msrv_auth->MA_next= msrv_def->MD_authorization;
      msrv_def->MD_authorization= msrv_auth;
    }
  }

  fclose (fi);

  return msrv_def;
}
