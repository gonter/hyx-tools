/*
 *  FILE %nl_kr/tasgml.c
 *
 *  textual analysis with TA_OBJECT
 *
 *  written:       1994-06-01
 *  latest update: 1999-11-28 13:06:43
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/ta.h>

/* ------------------------------------------------------------------------ */
int main (int argc, char *argv[])
{
  FILE *fi;
  struct TA_SOURCE tas;

  if (argc < 2) return 0;

  if ((fi= fopen (argv[1], "rb")) == (FILE *) 0) return 0;
printf ("opening %s\n", argv[1]);
  tas.TAS_filename= argv[1];
  tas.TAS_file= fi;
  tao_rd_sgml_body (&tas);
  fclose (fi);

  return 0;
}
