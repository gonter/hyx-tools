/*
 *  FILE ~/usr/nl_kr/lib/nl_00119.c
 *
 *  print veronica style results
 *
 *  written:       1993-05-01
 *  latest update: 1995-07-19
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_veronica_hit_list (
FILE *fo,
char *veronica_file,
struct WORD_REF_LIST *wrl)
{
  FILE *vf;
  int lines= 0;

  if (wrl == (struct WORD_REF_LIST *) 0) return 0;

  if ((vf= fopen (veronica_file, "rb")) == (FILE *) 0)
  {
    fprintf (stderr, "can't open veronica file %s\n", veronica_file);
    return -1;
  }

  for (; wrl != (struct WORD_REF_LIST *) 0; wrl= wrl->WRL_next)
  {
    lines += lmd_print_veronica_docinfo_list (fo, vf, wrl->WRL_dil);
  }

  fclose (vf);

  return lines;
}
