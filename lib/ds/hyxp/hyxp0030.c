/*
 *  FILE %ds/hyxp/hyxp0030.c
 *
 *  Verwaltung von TAG Defintionen
 *
 *  written:       1994-12-22
 *  latest update: 2001-02-18 17:40:38
 *  $Id: hyxp0030.c,v 1.2 2001/02/19 00:27:53 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int hyx_read_tag_definition (struct HYX_PARSER_CLASS *hpc, char *fn)
{
  FILE *fi;
  int rc;
#define LINE_SIZE 128
  char line [LINE_SIZE];

  fprintf (stderr, "note: reading tag definition file %s\n", fn);

  if ((fi= fopen (fn, "r")) == (FILE *) 0)
  {
    fprintf (stdout, "warning: file %s could not be opened\n", fn);
    return -1;
  }

  for (;;)
  {
    rc= fread_line (fi, line, LINE_SIZE);
    if (rc <= 0 && feof (fi)) break;
    hyx_process_tag_definition (hpc, line);
  }
  fclose (fi);

  return 0;
}
