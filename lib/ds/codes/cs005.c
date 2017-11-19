/*
 *  File %dpp/codes/cs005.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
static long index_str [256];
static long index_dat [256];

/* ------------------------------------------------------------------------ */
int cs_records2index (
struct CS_record *recs, /* records to be processed                          */
char *field[],          /* names of fields to use                           */
int fields,             /* number of fields                                 */
char *index_file,       /* name of file that holds index                    */
char *data_file,        /* name of file that holds the entity names         */
int verbose)            /* 1 -> be chatty on writing                        */
{
  FILE *fo= (FILE *) 0;
  int rv= 0;
  char *entity_name;
  long value;
  long position= 0L;
  long out_size;
  int i;
  struct CS_field *fld;

  for (i=0; i<256; i++) index_str [i]= -1L;
  for (i=0; i<256; i++) index_dat [i]= -1L;

  if (data_file != (char *) 0 && *data_file != 0)
  {
    fo = fopen (data_file, "wb");
    if (verbose)
      fprintf (stderr, "opening %s for writing entity data\n", data_file);
    if (fo == (FILE *) 0)
    {
      fprintf (stderr, "error: couldnt open %s for writing entity data!\n",
        data_file);
    }
  }

  for (; recs != (struct CS_record *) 0; recs= recs->CSr_next)
  {
    entity_name= (char *) 0;
    value= -1L;
    out_size= 0L;

    for (fld  = recs->CSr_fields;
         fld != (struct CS_field *) 0;
         fld  = fld->CSf_next)
    {
      if (strcmp (fld->CSf_name, "entity") == 0
         && fld->CSf_type == CSft_string)
      {
        entity_name= fld->CSf_string;
      }

      for (i= 0; i < fields; i++)
      {
        if (strcmp (fld->CSf_name, field[i]) == 0)
        { /* matching field name found */
            if (value == -1L && fld->CSf_type==CSft_number)
              value= fld->CSf_number;
        }
      }
    }

    if (entity_name != (char *) 0)
    {
      if (verbose)
        printf ("adding: %-24s pos=0x%08lX val=0x%08lX\n",
          entity_name, position, value);

      if (fo != (FILE *) 0)
      {
        recs->CSr_offset_str = position;
        position += (long) fwrite (entity_name, 1, strlen(entity_name)+1, fo);
      }

      if (value != -1L)
      {
        index_str [value] = recs->CSr_offset_str;
        index_dat [value] = recs->CSr_offset_dat;
      }
    }
  }

  fo= (FILE *) 0;
  if (index_file != (char *) 0 && *index_file != 0)
  {
    if (verbose)
      fprintf (stderr, "opening index file %s for writing\n", index_file);
    fo = fopen (index_file, "wb");
  }

  if (fo == (FILE *) 0)
  {
    fprintf (stderr, "error: couldnt open file %s to dump the index file!\n",
      index_file);
  }
  else
  {
    fwrite ((char *) index_str, 256, 4, fo);
    fclose (fo);
  }

  return rv;
}
