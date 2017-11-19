/*
 *  FILE %ds/lmd/nl_00407.c
 *
 *  initialize a LMD indexer dictionary context
 *
 *  written:       1990 06 04
 *                 1990 11 16: revision
 *                 1991 03 16: revision; AIX
 *                 1993-02-28: complete redesign of the refenece system
 *                 1994-12-19: isolated from wordcr04.c
 *  latest update: 1996-12-22 17:20:54
 *
 */

#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
void lmd_initialize_control (struct LMDC_CONTROL *lmdc)
{
  lmdc->LMDC_ytree= (struct YTREE *) 0;
  lmdc->LMDC_act_word_ref= (struct WORD_REF *) 0;

  lmdc->LMDC_word_index= 0L;
  lmdc->LMDC_cnt_sw_idx= 0L;
  lmdc->LMDC_stop_word_limit= STOP_WORD_LIMIT;
  lmdc->LMDC_max_word_count=  MAX_WORD_COUNT;
  lmdc->LMDC_min_wordlength=  MIN_WORDLENGTH;
  lmdc->LMDC_max_wordlength=  MAX_WORDLENGTH;
}
