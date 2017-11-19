/*
 *  FILE ~/usr/lexicon/lexpr001.c
 *
 *  written:       1991 04 19
 *  latest update: 1995-06-25
 *
 */

#include <stdio.h>
#include <gg/sbr.h>
#include <gg/parse.h>
#include "lexproc.h"

#ifdef JUNK
static struct LEXICON_INDEX *used_index;
static int used_index_count= 0;
static int used_sort_mode= 0;
#endif

static struct LEXICON_INDEX largest;

/* ------------------------------------------------------------------------ */
int init_by_size (int sort_mode, int sort_cnt)
{
  largest.LEXI_begin= -1L;
#ifdef MSDOS
  sort_mode;
  sort_cnt;
#endif

/****
fprintf (stdout, "init_by_size\n");
****/
#ifdef XXX
  used_index= calloc (sizeof (struct LEXICON_INDEX), sort_cnt);
  if (used_index == (void *) 0) return -1;
  used_sort_mode= sort_mode;
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
int process_by_size (struct LEXICON_INDEX *idx)
{
/****
fprintf (stdout, "process_by_size\n");
****/

  if (largest.LEXI_begin < 0L ||
      idx->LEXI_end - idx->LEXI_begin > largest.LEXI_end - largest.LEXI_begin)
  {
    largest.LEXI_begin          = idx->LEXI_begin;
    largest.LEXI_end            = idx->LEXI_end;
    largest.LEXI_cluster_number = idx->LEXI_cluster_number;
/****
fprintf (stdout, "init_by_size: largest: 0x%lX 0x%lX %ld\n",
         largest.LEXI_begin, largest.LEXI_end,
         largest.LEXI_end - largest.LEXI_begin +1L);
****/
  }

#ifdef XXX
  switch (used_sort_mode)
  {
    default:
      break;
  }
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
int finish_by_size (FILE *fhyx, FILE *fo)
{

/****
fprintf (stdout, "finish_by_size: largest: 0x%lX 0x%lX %ld\n",
         largest.LEXI_begin, largest.LEXI_end,
         largest.LEXI_end - largest.LEXI_begin +1L);
****/

  if (largest.LEXI_begin < 0L) return 0;
  fseek (fhyx, largest.LEXI_begin, 0);
  ftransfer (fhyx, fo, largest.LEXI_end-largest.LEXI_begin+1L);

  return 0;
}
