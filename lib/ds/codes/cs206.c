/*
 *  File %dpp/codes/cs206.c
 *
 *  written:       1993-06-12: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/codes.h>

static char *XX = "------------------------------\n";

/* ------------------------------------------------------------------------ */
int cs_print_tlate_table (FILE *fo, char *file_name, char *table_name)
{
#define MAX_ENTITY 40
  char entity [MAX_ENTITY+1];
  FILE *fi;
  int i, j, ch;

  if (file_name == (char *) 0
     || *file_name == 0
     || (fi= fopen (file_name, "rb")) == (FILE *) 0)
    return -1;

  fprintf (fo, "file %s; translation table %s\n", file_name, table_name);
  fprintf (fo, XX);
  fprintf (fo, "code | entity\n");
  fprintf (fo, XX);

  for (i= 0; i < 256; i++)
  {
    entity [MAX_ENTITY]= 0;
    for (j= 0; j < MAX_ENTITY; j++)
    {
      ch= fgetc (fi) & 0x00FF;
      entity[j]= (char) ch;
      if (ch == 0x00) break;
    }
    fprintf (fo, "0x%02X | %s\n", i, entity);
  }

  fprintf (fo, XX);

  fclose (fi);

  return 0;
}
