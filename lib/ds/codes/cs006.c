/*
 *  File %dpp/codes/cs006.c
 *
 *  written:       1992-12-25: g.gonter@ieee.org
 *  latest update: 1995-12-10
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/codes.h>

/* ------------------------------------------------------------------------ */
static int flag_common_base= 1;

/* ------------------------------------------------------------------------ */
int cs_records2table(
struct CS_record *recs,
char *src_attr [],
int src_attr_cnt,
char *dst_attr [],
int dst_attr_cnt,
int table_type,
long *table)
{
  int common_base= 0;           /* 1 -> both charsets have the same comon   */
                                /* base character set.                      */
  struct CS_field *fld;
  struct CS_field *src_fld;
  struct CS_field *dst_fld;
  int src_prio;
  int dst_prio;
  long src_code;
  int *spt;                     /* source priority table        */
  int *dpt;                     /* destination priority table   */
  int rv= 0;
  int i= 0;
  int j= 0;
  int k;

  if (table == (long *) 0) return -1;

  if (flag_common_base)
  {
    for (i= 0; i<src_attr_cnt; i++)
      for (j= 0; j<dst_attr_cnt; j++)
        if (strcmp (src_attr[i], dst_attr[j]) == 0)
        {
          common_base= 1;
          goto NEXT;
        }
  }

NEXT:
  if (common_base)
  {
    for (k= 0; k < 256; k++) table [k] = (long) k;
    fprintf (stderr,
      "info: common base translation from %s (%d) to %s (%d)\n",
      src_attr [i], i, dst_attr [j], j);

    if (i == j && i == 0)
    {
      fprintf (stderr,
        "info: translation from %s to %s is trivial...\n",
        src_attr [i], dst_attr [j]);
      return 0;
    }
    /* if a translation of (ascii,...) -> (ascii,...) is given, */
    /* then the conversion table is: table[i]=i without any     */
    /* thinkable modification, thus we can return immediately   */
  }
  else
  {
    i= j= 32000;
  }

  if ((spt= malloc (256*sizeof (int))) == (int *) 0) return -1;
  if ((dpt= malloc (256*sizeof (int))) == (int *) 0)
  {
    rv= -1;
    goto ERR;
  }

  for (k= 0; k < 256; k++) spt [k]= i;
  for (k= 0; k < 256; k++) dpt [k]= j;

  for (; recs != (struct CS_record *) 0; recs = recs->CSr_next)
  {
    src_fld= (struct CS_field *) 0;
    dst_fld= (struct CS_field *) 0;
    src_prio= 32000;
    dst_prio= 32000;

    for (fld  = recs->CSr_fields;
         fld != (struct CS_field *) 0;
         fld  = fld->CSf_next)
    {
      for (i= 0; i < src_attr_cnt; i++)
        if (strcmp (src_attr [i], fld->CSf_name) == 0
            && src_prio > i)
        {
          src_fld= fld;
          src_prio= i;
        }

      for (i= 0; i < dst_attr_cnt; i++)
        if (strcmp (dst_attr [i], fld->CSf_name) == 0
            && dst_prio > i)
        {
          dst_fld= fld;
          dst_prio= i;
        }
    }

    if (src_fld != (struct CS_field *) 0
       && src_fld->CSf_type == CSft_number
       && dst_fld != (struct CS_field *) 0
       && dst_fld->CSf_type == table_type)
    {
      src_code= src_fld->CSf_number;
      if (src_code >= 0L && src_code < 256L
        &&src_prio <= spt [src_code]
        &&dst_prio <= dpt [src_code])
      {
        table [src_code]= (table_type == CSft_number)
                          ? dst_fld->CSf_number
                          : (long) dst_fld->CSf_string;
        spt [src_code]= src_prio;
        dpt [src_code]= dst_prio;
      }
    }
  }

  free (dpt);
ERR:
  free (spt);

  return rv;
}

/* ------------------------------------------------------------------------ */
int set_common_base (int flag)
{
  flag_common_base= flag;

  return 0;
}
