/*
 *  FILE %lexicon/dict0009.c
 *
 *  store a pointer to an ENTRY_DESCRIPTOR in the queue maintained
 *  in a LEXICON_CONTROL structure
 *
 *  written:       1995-01-23
 *  latest update: 2000-08-26 15:18:36
 *  $Id: dict0009.c,v 1.2 2000/08/26 13:21:15 gonter Exp $
 *
 */

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_queue (
struct LEXICON_CONTROL *lcc,
struct ENTRY_DESCRIPTOR *ed,
int mark_dirty)
{
  struct ENTRY_QUEUE *e_q;
  struct LEXICON_GLOBAL_CONTROL *lgc;

  if (lcc == (struct LEXICON_CONTROL *) 0
      || (lgc= lcc->LC_lgc) == (struct LEXICON_GLOBAL_CONTROL *) 0
     ) return -1;

  if (ed == (struct ENTRY_DESCRIPTOR *) 0) return 0;

  if ((e_q= hyx_new_entry_queue()) == (struct ENTRY_QUEUE *) 0) return -1;

  e_q->EQ_ed= ed;
  e_q->EQ_is_dirty |= mark_dirty;

  *(lgc->LGC_EQ_append)= e_q;
  lgc->LGC_EQ_append= &e_q->EQ_next;
  lgc->LGC_EQ_count++;

  return 0;
}
