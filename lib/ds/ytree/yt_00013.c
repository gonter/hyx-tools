/*
 *  FILE %ds/ytree/yt_00013.c
 *
 *  written:       1994-12-08
 *  latest update: 1996-08-08 16:34:33
 *  $Id: yt_00013.c,v 1.3 2003/06/25 14:38:29 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/lookup.h>

#define LINE_SIZE 128
static char line [LINE_SIZE];

#define N_FIELDS 10
static char *fields [N_FIELDS];

/* ------------------------------------------------------------------------ */
int ytree_operations (
struct YTREE **ytpp,
FILE *fi,
FILE *fo)
{
  struct YTREE *yt;
  char *var_name;
  int cnt_fields;
  int rc;
  char *op;

  for (;;)
  {
    fputs ("% ", fo);
    fread_line (fi, line, LINE_SIZE);
    if (line [0] == '#') continue;
    if (feof (fi)) break;

    cnt_fields= isolate_tokens (line, (char **) fields, N_FIELDS);

    if (cnt_fields < 1) continue;
    op= fields [0];
    if (strcmp (op, "quit") == 0
        || strcmp (op, "\004") == 0
        || strcmp (op, "exit") == 0
       ) break;

    if (strcmp (op, "set") == 0 && cnt_fields == 3)
    {
      if ((yt= ytree_insert_word (ytpp, (unsigned char *) fields [1]))
          == (struct YTREE *) 0)
      {
        fprintf (fo, "error: yt == NIL\n");
        break;
      }
      if (yt->YT_flags & YTflag_EOW)
      {
        char *cp;
        cp= (char *) yt->YT_info;
        fprintf (fo, "previous value was %s\n",
                 (cp == (char *) 0) ? "NIL" : cp);
        if (cp != (char *) 0) free (cp);
      }
      yt->YT_info= (long) strdup (fields [2]);
      yt->YT_flags |= YTflag_EOW;
      continue;
    }

    if (strcmp (op, "query") == 0 && cnt_fields == 2)
    {
      var_name= fields [1];
      yt= ytree_lookup_word (*ytpp, (unsigned char *) var_name);
      if (yt == (struct YTREE *) 0)
      {
        fprintf (fo, "%s is undefined!\n", var_name);
      }
      else
      {
        if (yt->YT_flags & YTflag_EOW)
        {
          fprintf (fo, "%s's value is \"%s\"\n", var_name, yt->YT_info);
        }
        else
        {
          fprintf (fo, "%s is an intermediate node!\n", var_name);
        }
      }
      continue;
    }

    if (strcmp (op, "delete") == 0 && cnt_fields == 2)
    {
      var_name= fields [1];
      rc= ytree_delete_word (ytpp, (unsigned char *) var_name);
      fprintf (fo, "rc= %d\n", rc);
      continue;
    }

    if (strcmp (op, "print") == 0 && cnt_fields == 1)
    {
      ytree_size (*ytpp);
      ytree_print (fo, *ytpp, 2);
      continue;
    }

    if (strcmp (op, "lut") == 0 && cnt_fields == 2)
    {
      int rc;
      rc= lut_process (fields [1], lut_ytree_entry, (void *) ytpp, 0L);
      printf ("rc=%d\n", rc);
      continue;
    }

    if (strcmp (op, "size") == 0 && cnt_fields == 1)
    {
      long s;
      s= ytree_size (*ytpp);
      printf ("size=%ld\n", s);
    }

    fprintf (fo, "invalid command or syntax\n");
  }
  return 0;
}
