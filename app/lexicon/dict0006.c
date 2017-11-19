/*
 *  FILE ~/usr/lexicon/dict0006.c
 *
 *  written:       1994-12-10: isolated from dictadd1.c
 *  latest update: 2000-08-26 15:17:12
 *  $Id: dict0006.c,v 1.2 2000/08/26 13:21:15 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>

/* statistics: ------------------------------------------------------------ */
extern long YTREE_ALLOCATED;
extern long YTREE_ALLOC_SIZE;
extern long _hyx_markup_allocated;
extern long _hyx_markup_freed;
extern long _hyx_text_allocated;
extern long _hyx_text_freed;
extern long _hyx_text_segment_allocated;
extern long _hyx_txsegm_freed;
extern long _hyx_text_segment_alloc_size;
extern long _hyx_txsegm_free_size;
extern long TAG_DEFINITION_allocated;

/* ------------------------------------------------------------------------ */
void memory_statistics (FILE *fo, long record_counter)
{
  fprintf (fo, "Record %ld\n", record_counter);
#ifdef MSDOS
  fprintf (fo, "mem avail 0x%04X\n", _memavl());
#endif

  fprintf (fo,
           "Markup nodes:   alloc=%9ld   free=%9ld   active=%9ld\n",
           _hyx_markup_allocated,
           _hyx_markup_freed,
           _hyx_markup_allocated-_hyx_markup_freed);

  fprintf (fo,
           "Text nodes:     alloc=%9ld   free=%9ld   active=%9ld\n",
           _hyx_text_allocated,
           _hyx_text_freed,
           _hyx_text_allocated-_hyx_text_freed);

  fprintf (fo,
           "Text Seg nodes: alloc=%9ld   free=%9ld   active=%9ld\n",
           _hyx_text_segment_allocated,
           _hyx_txsegm_freed,
           _hyx_text_segment_allocated-_hyx_txsegm_freed);

  fprintf (fo,
           "Text Seg size:  alloc=%9ld   free=%9ld   active=%9ld\n",
           _hyx_text_segment_alloc_size,
           _hyx_txsegm_free_size,
           _hyx_text_segment_alloc_size-_hyx_txsegm_free_size);

  fprintf (fo,
           "YTREE nodes:    alloc=%9ld   size=%9ld\n",
           YTREE_ALLOCATED,
           YTREE_ALLOC_SIZE);
}
