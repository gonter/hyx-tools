/*
 *  FILE %sbr/modtbl.c
 *
 *  derive module references
 *
 *  written:       1995-06-15
 *  latest update: 1997-08-15 14:09:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/sbr.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/filename.h>

static struct YTREE *modules= (struct YTREE *) 0;
static int initialized= 0;

/* ------------------------------------------------------------------------ */
int read_module_table (char *fnm)
{
  FILE *fi;
  struct YTREE *yt;
#define BUFFER_SIZE 256
#define N_FIELDS 2
  char buffer [BUFFER_SIZE];
  char *fields [N_FIELDS];
  int field_cnt;
  int rc;

  if (fnm == (char *) 0)
    fnm= set_etc_filename ((char *) 0, DEFAULT_MODULE_TABLE);

  initialized= 1;
  if ((fi= fopen (fnm, "r")) == (FILE *) 0) return -1;

  for (;;)
  {
    rc= fread_line (fi, buffer, BUFFER_SIZE);
    if (rc <= 0 && feof (fi)) break;
    if (buffer [0] == '#') continue;

    field_cnt= split_string (buffer, ':', fields, N_FIELDS);
    if (field_cnt != 2) continue;

    if ((yt= ytree_insert_word (&modules, fields [0])) != (struct YTREE *) 0)
    {
      yt->YT_flags= YTflag_EOW;
      yt->YT_info= (long) strdup (fields [1]);
    }
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
char *get_module_directory (char *fnm)
{
  struct YTREE *yt;

  if (!initialized) read_module_table ((char *) 0);

  if ((yt= ytree_lookup_word (modules, fnm)) != (struct YTREE *) 0
      || (ytree_lookup_word_get_lng () > 0
          && (yt= ytree_lookup_word_get_last ())
         )
     )
  {
    if (yt->YT_flags & YTflag_EOW) return (char *) yt->YT_info;
  }

  return DEFAULT_MODULE_DIR;
}
