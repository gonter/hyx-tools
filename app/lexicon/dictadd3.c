/*
 *  FILE %lexicon/dictadd3.c
 *
 *  - t2d:
 *    Beschleunigung von Updates
 *
 *  written:       1991 03 17
 *  latest update: 2000-08-26 15:16:15
 *  $Id: dictadd3.c,v 1.3 2004/05/08 15:40:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/hytxt.h>
#include <gg/parse.h>
#include <gg/strings.h>

#ifndef MSDOS
#include <unistd.h>
#endif

/* ------------------------------------------------------------------------ */
int dict_update_entry (
struct HYX_PARSER_CLASS *hpc,
struct HYX_CLUSTER_CONTROL *hcc,
struct LEXICON_CONTROL *lcc,
char *frame_name,
struct TEXT_ELEMENT *tx_new_entry,
hyx_output_processor *op,
void *op_client_data,
int verbose_level)              /* to chat or not to chat ...               */
{
  struct TEXT_ELEMENT *lexicon_entry= (struct TEXT_ELEMENT *) 0;
                                /* Eintrag aus dem Lexicon als Liste        */
  struct ENTRY_DESCRIPTOR *ed=  /* descriptor of found word                 */
    (struct ENTRY_DESCRIPTOR *) 0;
  char *divide_file;            /* file name for divide mode                */
  struct LEXICON_GLOBAL_CONTROL *lgc;
  int is_dirty= 0;              /* entry needs to be written                */
  int mode;                     /* processing mode, see parse.h             */
  int rc;

  if (lcc == (struct LEXICON_CONTROL *) 0
      || hcc == (struct HYX_CLUSTER_CONTROL *) 0
      || (lgc= lcc->LC_lgc) == (struct LEXICON_GLOBAL_CONTROL *) 0
     ) return -1;

{ /* ### BEGIN read_existing_entry (hcc, frame_name) ### or so ... */
  /* also merges new entry to existing entry */
  struct YTREE *yt=             /* Endknoten des gesuchten bzw.             */
    (struct YTREE *) 0;         /* eingesetzten Wortes                      */
  /* return: rc, ed */

  switch (mode= hcc->HCC_dict_mode)
  {
    case DAMODE_CHECK:
    case DAMODE_DIVIDE1:
    case DAMODE_DIVIDE2:
    case DAMODE_DIVIDE3:
      goto SKIP;

    case DAMODE_LOOKUP:
      if ((yt= ytree_lookup_word (hcc->HCC_ytree,
                                  (unsigned char *) frame_name))
          == (struct YTREE *) 0)
        goto SKIP;
      break;

    case DAMODE_MERGE:
    case DAMODE_REPLACE:
      if ((yt= ytree_insert_word (&hcc->HCC_ytree,
                                  (unsigned char *) frame_name))
          == (struct YTREE *) 0)
      {
        fprintf (stdout, "error: dictadd1: yt == NIL !!!\n");
        return -1;
      }
      break;
  }

  if ((ed= (struct ENTRY_DESCRIPTOR *) yt->YT_info)
       == (struct ENTRY_DESCRIPTOR *) 0
     && hcc->HCC_lut_mode == HCC_lm_incremental)
  {
    long idx;

    if ((idx= hyx_get_index (hcc->HCC_f_idx, hcc->HCC_f_lut, hcc->HCC_f_xfn,
                             frame_name)) >= 0L)
    {
      yt->YT_info= idx;
      yt->YT_flags |= YTflag_EOW;
      if (ytree_index_to_entry_descriptor (yt, (void *) 0) == 0)
        ed= (struct ENTRY_DESCRIPTOR *) yt->YT_info;
    }
  }

  if (ed == (struct ENTRY_DESCRIPTOR *) 0)
  {
    if (verbose_level > 0) printf ("(new) ");
    if ((ed= (struct ENTRY_DESCRIPTOR *)
             calloc (sizeof (struct ENTRY_DESCRIPTOR), 1))
        == (struct ENTRY_DESCRIPTOR *) 0)
    {
      fprintf (stdout, "error: dictadd1: ed == NIL !!!\n");
      return -1;
    }

    ed->ED_status= ED_stat_is_new;
    yt->YT_info= (long) ed;   /* ED_index == 0L: get the next free entry  */
    yt->YT_flags |= YTflag_EOW;
    lexicon_entry= tx_new_entry;
    tx_new_entry= (struct TEXT_ELEMENT *) 0;
  }
  else
  {
    if (ed->ED_index >= hcc->HCC_next_index)
    {
      fprintf (stdout,
               "error: dictadd1: structural error in lexicon, %s %s %s\n",
               hcc->HCC_fnm_hyx, hcc->HCC_fnm_idx, hcc->HCC_fnm_lut);
      fprintf (stdout, 
       "       ed->ED_index >= hcc->HCC_next_index! (0x%08lX >= 0x%08lX)\n",
               ed->ED_index, hcc->HCC_next_index);
      return -1;
    }

    /* ASSERTION: at this point, ed is a pointer to the entry */
    /* descriptor of the newly read entry                     */
    if (mode == DAMODE_MERGE || mode == DAMODE_LOOKUP)
    {
      if (ed->ED_te == (struct TEXT_ELEMENT *) 0)
      {
        if (verbose_level > 0) printf ("(old) ");
        rc= hyx_parse_hyx_frame (hpc, hcc->HCC_fnm_hyx, hcc->HCC_fnm_idx,
                                ed->ED_index, &lexicon_entry,
                                lcc->LC_end_tags, lcc->LC_end_tag_count);

        if (rc == -1) return -1;

        dict_restructure_new_entry (hpc, &lexicon_entry, (char *) 0, 0,
              lcc->LC_do_strip,
              (struct TEXT_ELEMENT *) 0,
              (struct TEXT_ELEMENT *) 0);
      }
      else
      {
        if (verbose_level > 0) printf ("(get) ");
        lexicon_entry= ed->ED_te;

        /* reset entry in entry descriptor to avoid multiple flushes */
        /* <confused> why exactly is that needed? */
        ed->ED_te= (struct TEXT_ELEMENT *) 0;
        free (ed->ED_frame_name);
        ed->ED_frame_name= (char *) 0;
        /* </confused> */

        lgc->LGC_EQ_count--;
      }

      if (lexicon_entry == (struct TEXT_ELEMENT *) 0)
      {
        fprintf (stdout, "error: lexicon_entry == NIL\n");
        return -1;
      }

      if (mode == DAMODE_MERGE)
      {
        /* Eintraege kombinieren und zu einem zusammenfassen ... */
        dict_combine_entries (&lexicon_entry, &tx_new_entry);
      }
    }
    else
    { /* check this for entries stored in the entry descriptor! */
      if (mode == DAMODE_REPLACE)
      {
        if (verbose_level > 0) printf ("(rep) ");
      }
      lexicon_entry= tx_new_entry;
      tx_new_entry= (struct TEXT_ELEMENT *) 0;
    }
  }
  
} /* ### END reading existing entry ### or so ... */

  /* ASSERTION: at this point, ed is a pointer to the   */
  /* entry descriptor of the newly read entry           */

  if (verbose_level > 0) printf ("ID=%08lX\n", ed->ED_index);

SKIP:
  switch (mode= hcc->HCC_dict_mode)
  {
    case DAMODE_MERGE:
    case DAMODE_REPLACE:
    case DAMODE_LOOKUP:
      is_dirty= 1;

      if (mode == DAMODE_LOOKUP)
      {
        is_dirty= 0;
        if (op != (hyx_output_processor *) 0)
          (*op) (op_client_data, lexicon_entry);
      } 

#ifdef IMMED_WRITE
      if (is_dirty)
      {
        rc= write_lexicon_entry (hcc->HCC_fnm_hyx, hcc->HCC_fnm_idx,
                                 &ed->ED_index, frame_name, lexicon_entry,
                                 &hcc->HCC_next_index, lcc->LC_write_nl);
        if (rc == -1) return -1;
      }
#endif

      if (ed == (struct ENTRY_DESCRIPTOR *) 0)
      { /* DAMODE_LOOKUP can result in a ed NIL pointer */
        break;
      }

      /*** printf ("*** storing entry '%s'\n", frame_name); ***/
      ed->ED_frame_name= strdup (frame_name);
      ed->ED_te= lexicon_entry;
      lexicon_entry= (struct TEXT_ELEMENT *) 0;
      dict_queue (lcc, ed, is_dirty);  /* queue up entry */
      if (lgc->LGC_EQ_count >= lgc->LGC_queue_size)
        dict_flush_queue (hcc, lcc);
      break;

    case DAMODE_DIVIDE1:
    case DAMODE_DIVIDE2:
    case DAMODE_DIVIDE3:
      if (verbose_level > 0) printf ("(divide)\n");
      divide_file= get_divided_lexicon (hcc->HCC_fnm_hyx, mode, frame_name);
      hcc->HCC_next_index= -1L;
      lexicon_entry= tx_new_entry;
      tx_new_entry= (struct TEXT_ELEMENT *) 0;
      rc= write_lexicon_entry (divide_file, hcc->HCC_fnm_idx,
                               &hcc->HCC_next_index, frame_name,
                               lexicon_entry, &hcc->HCC_next_index, 1);
      if (rc == -1) return -1;
      break;

    case DAMODE_CHECK:
      if (verbose_level > 0) printf ("(test)\nno update\n");
      break;
  }

  /* ### @@@ T2D ??? ev. loeschen */
  if (verbose_level > 1)
  {
    struct MARKUP *markup_new;

    if (hyx_text_to_markup (hpc, lexicon_entry, &markup_new) != -1)
    {
      lexicon_entry= (struct TEXT_ELEMENT *) 0;
      display_markup (stdout, hpc, (struct TEXT_ELEMENT *) markup_new, 0, 1, 1, 1);
      hyx_frtx_elem_list ((struct TEXT_ELEMENT *) markup_new);
    }
  }

  hyx_frtx_elem_list (lexicon_entry);
  hyx_frtx_elem_list (tx_new_entry);

  return 0;
}
