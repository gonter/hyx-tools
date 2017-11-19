/*
 *  FILE %ds/lmd/nl_00402.c
 *
 *  create a word reference entry
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *                 1994-12-19: isolated from wordcr04.c
 *  latest update: 2001-02-04 21:09:50
 *  $Id: nl_00402.c,v 1.6 2001/10/08 15:01:25 gonter Exp $
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gg/ytree.h>
#include <gg/lookup.h>
#include <gg/dirty.h>

/* ------------------------------------------------------------------------ */
int lmd_idx (
struct LMDC_CONTROL *lmdc,
char *string,           /* word                                             */
long document_id,       /* document identification code                     */
                        /* < 0L ... the word is a stop word                 */
                        /* = 0L ... the word is a hit word, no document yet */
                        /* > 0L ... the word comes from a document          */
long document_ptr,      /* document pointer code to be placed into DOCID    */
char *document_id_str,  /* id string for document                           */
int loc_operator,       /* mode for using the loc_code                      */
int loc_number,         /* which location code to use                       */
long loc_code)          /* position code                                    */
{
  struct YTREE *p;
  int rc;

  lmdc->LMDC_act_word_ref= (struct WORD_REF *) 0;

  if (nl_key_valid (string) == -1)
  {
    lmd_error04 ("invalid key");
    dump (stdout, string, strlen (string));
    return -2;        /* this is done twice!      */
  }

  lmdc->LMDC_cnt_sw_idx++;

  if ((p= ytree_insert_word (&lmdc->LMDC_ytree, (unsigned char *) string))
      == (struct YTREE *) 0)
  {
NO_MEMORY:
    lmd_error04 ("Out of Memory");
    return -1;
  }

  p->YT_flags |= YTflag_EOW;

#ifdef JUNK
  if (p->YT_info < 0L) return 0; /* stop word, so stop ... */
#endif

  /* otherwise it's a new word */
  if ((lmdc->LMDC_word_index= p->YT_info) == 0L)
  { /* an new word was found */
    if (document_id >= 0L)
    {
      if ((lmdc->LMDC_act_word_ref= lmd_new_word_ref ())
           == (struct WORD_REF *) 0)
        goto NO_MEMORY;

      p->YT_info= (long) lmdc->LMDC_act_word_ref;
    }
    else p->YT_info= 0L;
  }
  else
  {
    lmdc->LMDC_act_word_ref= (struct WORD_REF *) p->YT_info;
  }

  if ((lmdc->LMDC_word_index= p->YT_info) != 0L)
  {
    if (document_id >= 0L)
    { /* store word information */
      rc= lmd_word_statistics (lmdc, lmdc->LMDC_act_word_ref, string,
                               document_id, document_ptr, document_id_str,
                               ADD_WORD_REF,
                               loc_operator, loc_number, loc_code);

      if (rc != 0)
      {
        lmd_error04 ("Out of Memory");
        return -1;
      }

#ifdef __COMMENT__
Does it make sense to delete a word from the document list again?
#endif /* _COMMENT */
    }
    else
      if (document_id < 0L)
      { /* now a stop word, but previously there was info for the word */
        lmd_word_statistics (lmdc, lmdc->LMDC_act_word_ref, string,
                             document_id, document_ptr, document_id_str,
                             DEL_WORD_REF,
                             loc_operator, loc_number, loc_code);
        p->YT_info= 0L;
      }
  }

  return 0;
}
