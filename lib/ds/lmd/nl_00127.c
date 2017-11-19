/*
 *  FILE ~/usr/nl_kr/lib/nl_00127.c
 *
 *  construct a TERM structure
 *
 *  written:       1994-08-24
 *  latest update: 1995-07-31
 *
 */

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct TERM_EVAL *lmd_build_term_eval (char *str, struct WORD_REF_LIST *wrl)
{
  struct TERM_EVAL *te;

  if ((te= lmd_new_term_eval ()) != (struct TERM_EVAL *) 0)
  {
    te->TE_string= strdup (str);
    te->TE_wrl= wrl;
    te->TE_operator= lmd_get_interpretation (str);

#ifdef DEBUG
    printf ("lmd_build_term_eval: op=0x%08lX\n", te->TE_operator);
#endif /* DEBUG */

    if (wrl != (struct WORD_REF_LIST *) 0)
    {
      te->TE_dil= wrl->WRL_dil;
    }
  }

  return te;
}
