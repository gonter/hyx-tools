/*
 *  FILE %ds/varspace/varsp007.c
 *
 *  written:       1994-12-26
 *  latest update: 1996-01-21 23:39:10
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/varspace.h>
#include <gg/attlist.h>

#define LINE_SIZE 128
static char line [LINE_SIZE];

#define N_FIELDS 10
static char *fields [N_FIELDS];

/* ------------------------------------------------------------------------ */
int vs_operations (
struct YTREE **ytpp,
FILE *fi,
FILE *fo)
{
  struct VAR_SPACE *vsp;
  char *var_name;
  int cnt_fields;
  int rc;
  long xval;

  for (;;)
  {
    fputs ("% ", fo);
    fread_line (fi, line, LINE_SIZE);
    if (line [0] == '#') continue;
    cnt_fields= isolate_tokens (line, fields, N_FIELDS);

    if (cnt_fields < 1) continue;
    if (strcmp (fields [0], "quit") == 0
        || strcmp (fields [0], "0x04") == 0
        || strcmp (fields [0], "exit") == 0
       ) break;

    if (strcmp (fields [0], "set") == 0 && cnt_fields == 3)
    {
      rc= vs_assign (ytpp, fields [1], (long) strdup (fields [2]),
                     (long) ALty_string_dup, '.');
      if (rc == -1)
      {
        fprintf (fo, "error: rc == -1\n");
        break;
      }
      continue;
    }

    if (strcmp (fields [0], "inc") == 0 && cnt_fields == 3)
    {
      xval= vs_increment (ytpp, fields [1],
                          get_parameter_value (fields [2]), 1, '.');
      fprintf (fo, "xval=%ld\n", xval);
      continue;
    }

    if (strcmp (fields [0], "pinc") == 0 && cnt_fields == 3)
    {
      xval= vs_increment (ytpp, fields [1],
                          get_parameter_value (fields [2]), 0, '.');
      fprintf (fo, "xval=%ld\n", xval);
      continue;
    }

    if (strcmp (fields [0], "query") == 0 && cnt_fields == 2)
    {
      var_name= fields [1];
      vsp= vs_query (*ytpp, var_name, '.');
      if (vsp == (struct VAR_SPACE *) 0)
      {
        fprintf (fo, "%s is undefined!\n", var_name);
      }
      else
      {
        switch ((int) vsp->VS_type)
        {
          case ALty_string:
          case ALty_string_dup:
            fprintf (fo, "string, value= '%s'\n", vsp->VS_value);
            break;
          case ALty_long:
            fprintf (fo, "long, value= 0x%08lX\n", vsp->VS_value);
            break;
          default:
            fprintf (fo, "unknown type %ld, value= 0x%08lX\n",
                     vsp->VS_type, vsp->VS_value);
            break;
        }
      }
      continue;
    }

#ifndef JUNK
    if (strcmp (fields [0], "delete") == 0 && cnt_fields == 2)
    {
      var_name= fields [1];
      rc= ytree_delete_word (ytpp, var_name);
      fprintf (fo, "rc= %d\n", rc);
      continue;
    }
#endif

    if (strcmp (fields [0], "print") == 0 && cnt_fields == 1)
    {
      ytree_print (fo, *ytpp, 2);
      continue;
    }

    fprintf (fo, "invalid command or syntax\n");
  }
  return 0;
}
