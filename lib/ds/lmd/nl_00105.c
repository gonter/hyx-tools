/*
 *  FILE %ds/lmd/nl_00105.c
 *
 *  dereferenciate a word
 *
 *  written:       1994-07-31
 *  latest update: 1995-07-30
 *  $Id: nl_00105.c,v 1.2 2002/01/29 08:01:42 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct WORD_REF_LIST *lmd_deref1 (
struct LMD_QUERY_SET *lmdqs,
char *str,
int min_wordlength,
int max_wordlength)
{
  int exact= 1;
  int wl;
  int ch;

#ifdef DEBUG
printf ("nl_00105: str='%s'\n", str);
#endif /* DEBUG */

  for (wl= 0;; wl++)
  {
    ch= str [wl] & 0x00FF;
    lmdqs->LMDQS_ext_pattern [wl]= (char) ch;
    if (ch == '*' || ch == '?')
    {
      str [wl]= 0;
      exact= 0;
    }
    if (ch == 0) break;
  }

  if (wl < min_wordlength) return (struct WORD_REF_LIST *) 0;
  if (wl > max_wordlength) str [max_wordlength]= 0;
  to_lower (str);

  if (exact) lmdqs->LMDQS_ext_pattern [0]= 0;
#ifdef DEBUG
printf ("nl_00105: str=%s ext=%s\n", str, lmdqs->LMDQS_ext_pattern);
#endif /* DEBUG */

  return lmd_deref_word (lmdqs, str, exact);
}
