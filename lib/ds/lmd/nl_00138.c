/*
 *  FILE ~/usr/nl_kr/lib/nl_00138.c
 *
 *  deref a word
 *
 *  written:       1993-07-30
 *  latest update: 1995-07-30
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/lookup.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
int lmd_store_word_ref (
char *str,
long info,
void *client_data)
{
  struct WORD_REF_LIST *new_wrl;
  struct LMD_QUERY_SET *lmdqs;

#ifdef DEBUG
printf ("nl_00138: str='%s' info=0x%08lX\n", str, info);
#endif /* DEBUG */

  if ((lmdqs= (struct LMD_QUERY_SET *) client_data)
      == (struct LMD_QUERY_SET *) 0) return -1;

  lmdqs->LMDQS_found_string [0]= 0;
  if (lmdqs->LMDQS_pfx != (char *) 0)
    strcpy (lmdqs->LMDQS_found_string, lmdqs->LMDQS_pfx);
  if (str != (char *) 0)
    strcpy (lmdqs->LMDQS_found_string + lmdqs->LMDQS_pfx_lng, str);

  /* In case if an extra match pattern is definied, take the word only      */
  /* if it matches with that pattern.                                       */
  if (lmdqs->LMDQS_ext_pattern [0] != 0)
  {
    if (match (lmdqs->LMDQS_ext_pattern, lmdqs->LMDQS_found_string) <= 0)
      return 0;
  }

#ifdef DEBUG
printf ("nl_00138: store_word_ref (%s, 0x%08lX) [%s]\n",
str, info, lmdqs->LMDQS_found_string);
#endif /* DEBUG */

  if ((new_wrl= lmd_new_word_ref_list ()) == (struct WORD_REF_LIST *) 0)
  {
    lmdqs->LMDQS__error_flag= 1;
    return 0;
  }

  if (lmd_find_word_ref (lmdqs->LMDQS_F_wr, info, &new_wrl->WRL) == -1)
    lmdqs->LMDQS__error_flag= 1;

  if (lmdqs->LMDQS_found_string [0] != 0)
    new_wrl->WRL_string= strdup (lmdqs->LMDQS_found_string);

  new_wrl->WRL_next= *lmdqs->LMDQS__wrl;
  *lmdqs->LMDQS__wrl= new_wrl;
  lmdqs->LMDQS__wrl= &new_wrl->WRL_next;

  return 0;
}
