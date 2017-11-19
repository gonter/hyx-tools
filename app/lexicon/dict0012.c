/*
 *  FILE %lexicon/dict0012.c
 *
 *  written:       1995-06-25
 *  latest update: 1996-10-10  0:15:49
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/sbr.h>
#include <gg/hytxt.h>
#include <gg/strings.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_read_setup_file (
struct HYX_CLUSTER_CONTROL *hcc,
char *fn,
char *line,
int MAX_LINE,
char **tag_definition)
{
  FILE *fi;

#ifdef MSDOS
  MAX_LINE;
#endif

  if (fn == (char *) 0 || *fn == 0) return 0;

  /* read lexicon setup file */
  if ((fi= fopen (fn, "rt")) == (FILE *) 0)
  {
    /********
    fprintf (stdout, "error opening setup file \'%s\'\n", fn);
    fprintf (stdout, "... using default values\n");
    ********/
    return 0;
  }

  for (;;)
  {
    fscanf (fi, "%s", line);
    if (feof (fi)) break;
    if (line [0] == '#')
    {
READ_NEXT:
      trash_until_eol (fi);
      continue;
    }

    if (strncmp (line, "cluster", 3) == 0)
    {
      fscanf (fi, "%s", line);
      hcc_set_cluster_name (hcc, line);
    } else
    if (strncmp (line, "lex", 3) == 0)
    {
      fscanf (fi, "%s", line);
      str_assign (&hcc->HCC_fnm_hyx, line);
    } else
    if (strncmp (line, "idx", 3) == 0)
    {
      fscanf (fi, "%s", line);
      str_assign (&hcc->HCC_fnm_idx, line);
    } else
    if (strncmp (line, "main", 4) == 0)
    {
      fscanf (fi, "%s", line);
      str_assign (&hcc->HCC_fnm_lut, line);
    } else
    if (strncmp (line, "tag", 3) == 0)
    {
      fscanf (fi, "%s", line);
      str_assign (tag_definition, translate_logic_filename (line));
    } else goto READ_NEXT;
  }
  fclose (fi);

  return 0;
}
