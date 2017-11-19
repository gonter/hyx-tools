/*
 *  FILE %ds/lmd/nl_00128.c
 *
 *  construct a TERM structure
 *
 *  written:       1994-08-24
 *  latest update: 1995-12-26
 *  $Id: nl_00128.c,v 1.4 2001/08/27 15:29:02 gonter Exp $
 *
 */

/** #define DEBUG **/
#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct TERM_EVAL *lmd_evaluate_terms (
struct TERM_EVAL *te_list,
long opcode)
{
  struct TERM_EVAL *te;
  struct TERM_EVAL *tte;
  struct DOCUMENT_INFO_LIST *dil_opr;
  struct DOCUMENT_INFO_LIST *dil_acc= (struct DOCUMENT_INFO_LIST *) 0;
  struct WORD_REF_LIST *wrl;
  long interpr;
  int elements= 0;

  if ((tte= lmd_new_term_eval ()) == (struct TERM_EVAL *) 0) goto END;

  for (te= te_list; te != (struct TERM_EVAL *) 0; te= te->TE_right)
  {
#ifdef DEBUG
    printf ("evaluate: %s %ld\n", te->TE_string, te->TE_operator);
#endif /* DEBUG */

    if ((interpr= te->TE_operator) == WRint_ignore) continue;

    if (interpr == WRint_logic_and || interpr == WRint_logic_or)
    {
      opcode= interpr;
      continue;  /* don't perform operations involving the operator!!! */
    }

    if ((wrl= te->TE_wrl) != (struct WORD_REF_LIST *) 0)
    {
#ifdef DEBUG
printf ("wrl=0x%08lX wrl->WRL_string='%s', WRL=...\n", wrl, wrl->WRL_string);
lmd_print_word_ref_info (stdout, &wrl->WRL);
#endif /* DEBUG */

      if (wrl->WRL.WR_count < 0   /* huh?  seems like dead code */
          || wrl->WRL.WR_docinfo_count == 0
         )
      { /* Stop Word?  Don't use Stop Words in the evaluation */
        /* GG 1995-12-15 14:23:42 */
        continue;
      }
    }

    dil_opr= lmd_dil_accumulate (te->TE_wrl);

#ifdef DEBUG
printf ("=========================\n");
printf ("accumulator:\n");
lmd_print_document_info_list (stdout, dil_acc);
printf ("-------------------------\n");
printf ("add:\n");
lmd_print_document_info_list (stdout, dil_opr);
printf ("-------------------------\n");
#endif /* DEBUG */

    dil_acc= (elements++ > 0)
             ? lmd_dil_operator (dil_acc, dil_opr, opcode)
             : dil_opr;

#ifdef DEBUG
printf ("result:\n");
lmd_print_document_info_list (stdout, dil_acc);
printf ("=========================\n");
#endif /* DEBUG */
  }

  tte->TE_dil= dil_acc;

END:
  return tte;
}
