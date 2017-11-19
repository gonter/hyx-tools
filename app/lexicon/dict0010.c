/*
 *  FILE %lexicon/dict0010.c
 *
 *  flush all queued-up entries if they're dirty.
 *
 *  written:       1995-01-23
 *  latest update: 2000-08-26 15:17:56
 *  $Id: dict0010.c,v 1.2 2000/08/26 13:21:15 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/hytxt.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_flush_queue (
struct HYX_CLUSTER_CONTROL *hcc,
struct LEXICON_CONTROL *lcc)
{
  struct ENTRY_QUEUE *e_q, *e_q2;
  struct ENTRY_DESCRIPTOR *ed;
  struct LEXICON_GLOBAL_CONTROL *lgc;

  if (hcc == (struct HYX_CLUSTER_CONTROL *) 0
      || lcc == (struct LEXICON_CONTROL *) 0
      || (lgc= lcc->LC_lgc) == (struct LEXICON_GLOBAL_CONTROL *) 0
     ) return -1;

#ifdef MSDOS
  printf ("flushing %d entries; mem avail=0x%04X\n",
          lgc->LGC_EQ_count, _memavl());
#else
  printf ("flushing %d entries\n", lgc->LGC_EQ_count);
#endif

  for (e_q= lgc->LGC_EQ_first;
       e_q != (struct ENTRY_QUEUE *) 0;)
  {
    e_q2= e_q->EQ_next;

    if ((ed= e_q->EQ_ed) != (struct ENTRY_DESCRIPTOR *) 0
       && ed->ED_te != (struct TEXT_ELEMENT *) 0
       && ed->ED_frame_name != (char *) 0)
    {
      if (e_q->EQ_is_dirty)
      {
        if (write_lexicon_entry (hcc->HCC_fnm_hyx, hcc->HCC_fnm_idx,
                                 &ed->ED_index, ed->ED_frame_name, ed->ED_te,
                                 &hcc->HCC_next_index, lcc->LC_write_nl)
            == -1)
        {
          printf ("dict_flush_queue: error writing frame '%s'\n",
                  ed->ED_frame_name);
          printf ("                : stopping flush!\n");

          lgc->LGC_EQ_first= e_q;
          lgc->LGC_EQ_append= &e_q->EQ_next;

          return -1;
        }
      }

      if (hcc->HCC_lut_mode != HCC_lm_incremental
          || ed->ED_status != ED_stat_is_new
         )
      {
        free (ed->ED_frame_name);
        ed->ED_frame_name= (char *) 0;
      }
      else printf ("new frame: %s\n", ed->ED_frame_name);

      hyx_frtx_elem_list (ed->ED_te);
      ed->ED_te= (struct TEXT_ELEMENT *) 0;
    }

    free (e_q);
    e_q= e_q2;
  }

  lgc->LGC_EQ_first= (struct ENTRY_QUEUE *) 0;
  lgc->LGC_EQ_append= &lgc->LGC_EQ_first;
  lgc->LGC_EQ_count= 0;

  return 0;
}
