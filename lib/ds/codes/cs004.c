/*
 *  File %dpp/codes/cs004.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1995-12-09
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/ytree.h>
#include <gg/dpp.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
int cs_records2ytree (
struct CS_record *recs, /* records to be processed                          */
char *field [],         /* names of fields to use                           */
long  tags [],          /* tag codes for field names                        */
int fields,             /* number of fields                                 */
char *lut_file,         /* name of LUT file to be written                   */
char *data_file,        /* name of data file to be written                  */
int verbose,            /* 1 -> be chatty while compiling info              */
int compact,            /* 1 -> compact LUT, info contains code             */
                        /*      of first matching field                     */
int all)                /* 1 -> use all entities, even without code         */
{
  FILE *fo= (FILE *) 0;
  int rv= 0;
#define MAX_entity_names 24
  char *entity_name [MAX_entity_names];
  int entity_names;
  long value;
  long position= 0L;
  long out_size;
  int i;
  struct CS_field *fld;
  struct YTREE *ytree= (struct YTREE *) 0;
  struct YTREE *yt;

  if (!compact)
  {
    if (data_file != (char *) 0 && *data_file != 0)
    {
      fo= fopen (data_file, "wb");
      if (verbose)
        fprintf (stderr, "opening %s for writing entity data.\n",
          data_file);
      if (fo == (FILE *) 0)
      {
        fprintf (stderr, "error: couldnt open %s for writing entity data!\n",
          data_file);
      }
    }
  }

  for (; recs != (struct CS_record *) 0; recs= recs->CSr_next)
  {
    entity_names= 0;
    value= -1L;
    out_size= 0L;

    for (fld  = recs->CSr_fields;
         fld != (struct CS_field *) 0;
         fld  = fld->CSf_next)
    {
      if (strcmp (fld->CSf_name, "entity") == 0
         && fld->CSf_type == CSft_string)
      {
        entity_name [entity_names++]= fld->CSf_string;
      }

      for (i= 0; i < fields; i++)
      {
        if (strcmp (fld->CSf_name, field[i]) == 0)
        { /* matching field name found */
          if (compact)
          {
            if (value == -1L && fld->CSf_type==CSft_number)
              value= fld->CSf_number;
          }
          else
          { /* write to data file ############ */
            if (fo != (FILE *) 0)
            {
              if (fld->CSf_type == CSft_number)
              {
                dpp_fwrite_long (fo, 4L, 2);
                dpp_fwrite_long (fo, tags [i], 4);
                dpp_fwrite_long (fo, fld->CSf_number, 4);
                out_size += 10L;
              }
              else
              {
                long lng;

                lng= (long) (strlen (fld->CSf_string)+1);
                dpp_fwrite_long (fo, lng, 2);
                dpp_fwrite_long (fo, tags [i], 4);
                fwrite (fld->CSf_string, (int) lng, 1, fo);
                out_size += lng + 6L;
              }
            }
          }
        }
      }
    }

                                        /* further processing only if ...   */
    if (entity_names != 0               /* ... there is a entity name       */
        &&(!compact                     /* and the file is not compact      */
           || all                       /* or the all-option                */
           || value != -1L              /* or a value is given              */
          )
       )
    {
      for (i= 0; i < entity_names; i++)
      {
        if (verbose)
          printf ("adding: %-24s pos=0x%08lX val=0x%08lX\n",
            entity_name [i], position, value);

        if ((yt= ytree_insert_word (&ytree,
                                    (unsigned char *) entity_name [i]))
            == (struct YTREE *) 0)
        {
          fprintf (stderr, "error: yt==0 !!!\n");
          return -1;
        }

        yt->YT_flags |= YTflag_EOW;
        yt->YT_info= (compact) ? value : ((out_size) ? position : -1L);
      }
      recs->CSr_offset_dat= position;
      position += out_size;
    }
  }

  ytree_size (ytree);
  if (fo != (FILE *) 0) fclose (fo);

  fo= (FILE *) 0;
  if (lut_file != (char *) 0 && *lut_file != 0)
  {
    fo= fopen (lut_file, "wb");
    if (verbose)
      fprintf (stderr, "opening %s for writing entity lut.\n",
        lut_file);
  }

  if (fo == (FILE *) 0)
  {
    fprintf (stderr, "error: couldnt open file %s to dump the entity lut!\n",
      lut_file);
  }
  else
  {
    ytree_dump (fo, ytree);
    fclose (fo);
  }

  return rv;
}
