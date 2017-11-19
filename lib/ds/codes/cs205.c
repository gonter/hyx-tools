/*
 *  File %dpp/codes/cs205.c
 *
 *  written:       1993-06-11: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
struct CS_tlate_table *cs_load_tlate_table (char *file_name, char *table_name)
{
#define MAX_ENTITY 40
  char entity [MAX_ENTITY+1];
  struct CS_tlate_table *ttbl= (void *) 0;
  FILE *fi;
  int i, j, ch;

  if (file_name == (char *) 0
     || *file_name == 0
     || (fi= fopen (file_name, "rb")) == (FILE *) 0)
    goto STOP;

  if ((ttbl= calloc (sizeof (struct CS_tlate_table), 1))
      == (void *) 0) goto ERR;

  ttbl->CStt_table_name= strdup (table_name);
  ttbl->CStt_file_name= strdup (file_name);

  for (i= 0; i < 256; i++)
  {
    entity [MAX_ENTITY]= 0;
    for (j= 0; j < MAX_ENTITY; j++)
    {
      ch= fgetc (fi) & 0x00FF;
      entity[j]= (char) ch;
      if (ch == 0x00) break;
    }
    ttbl->CStt_table [i]= strdup (entity);
  }

ERR:
  fclose (fi);
STOP:
  return ttbl;
}
