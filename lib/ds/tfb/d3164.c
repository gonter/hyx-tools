/*
 *  FILE %ds/tfb/d3164.c
 *
 *  written:       1994-08-20
 *  latest update: 1995-11-11
 *
 */

#include <stdio.h>

#pragma pack(1)

/* ------------------------------------------------------------------------ */
#define FLD1_MAX 29
#define FLD2_MAX 30
struct DBF_D3164
{
  char rec_num;
  char nul1;
  char fld1_size;
  char fld1 [FLD1_MAX];
  char nul2;
  char fld2_size;
  char fld2 [FLD2_MAX];
} ;

/* ------------------------------------------------------------------------ */
int xout (FILE *fo, char *b, int siz)
{
  while (siz-- > 0) fputc (*b++, fo);
  return 0;
}

/* ------------------------------------------------------------------------ */
int convert_d3164 (FILE *fi, FILE *fo, int fld_sep, char *fn)
{
  struct DBF_D3164 dbf;
  int rc;

  for (;;)
  {
    rc= fread ((char *) &dbf, sizeof (struct DBF_D3164), 1, fi);
    /* printf ("rc=%d %d\n", rc, dbf.rec_num); */
    if (rc < 1) break;
    fprintf (fo, "%s%c%d%c",
             fn,
             fld_sep,
             dbf.rec_num,
             fld_sep);

    xout (fo, dbf.fld1, dbf.fld1_size);
    fputc (fld_sep, fo);

    xout (fo, dbf.fld2, dbf.fld2_size);
    fputc ('\n', fo);
  }
  return 0;
}


