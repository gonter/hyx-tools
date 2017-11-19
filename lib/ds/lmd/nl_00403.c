/*
 *  FILE %ds/lmd/nl_00403.c
 *
 *  lookup a word reference entry
 *
 *  written:       1996-12-22
 *  latest update: 1996-12-22 17:54:52
 *
 */

#include <string.h>
#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct WORD_REF *lmd_lookup_entry (
struct LMDC_CONTROL *lmdc,
char *string)                           /* word                             */
{
  struct YTREE *p;
  struct WORD_REF *rv= (struct WORD_REF *) 0;

  if (nl_key_valid (string) != -1
      && (p= ytree_lookup_word (lmdc->LMDC_ytree, (unsigned char *) string))
          != (struct YTREE *) 0
      && (p->YT_flags & YTflag_EOW)
      && (rv= (struct WORD_REF *) p->YT_info) != (struct WORD_REF *) 0
     )
  {
    lmdc->LMDC_act_word_ref= rv;
  }

  return rv;
}
