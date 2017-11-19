/*
 *  FILE %lexicon/dict0014.c
 *
 *  restructure text elements according to lexicon control
 *
 *  written:       1995-08-05
 *  latest update: 2001-02-18 18:06:39
 *  $Id: dict0014.c,v 1.3 2002/01/22 03:07:27 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long dict_restructure2_entry (
struct HYX_PARSER_CLASS *hpc,
struct LEXICON_CONTROL *lcc,
struct TEXT_ELEMENT **tx_new_entry,
char *entry_key,
int entry_key_size)
{
  struct TEXT_ELEMENT *head_tag_text= (struct TEXT_ELEMENT *) 0;
  struct TEXT_ELEMENT *tail_tag_text= (struct TEXT_ELEMENT *) 0;

#ifdef PARSER_DEBUG_B
printf ("dict0014: hpc=0x%08lX lcc=0x%08lX tx_new_entry=0x%08lX entry_key=0x%08lX '%s'\n",
  hpc, lcc, tx_new_entry, entry_key, entry_key);
#endif /* PARSER_DEBUG_B */

  if (lcc == (struct LEXICON_CONTROL *) 0
      || tx_new_entry == (struct TEXT_ELEMENT **) 0
     ) return -1;

#ifdef PARSER_DEBUG_B
printf ("dict0014: 2: lcc->LC_head_tag_str=0x%08lX\n", lcc->LC_head_tag_str);
#endif /* PARSER_DEBUG_B */
  if (lcc->LC_head_tag_str != (char *) 0)
    head_tag_text= hyx_mktx_elem_and_segm (hpc, lcc->LC_head_tag_str,
                   (long) strlen (lcc->LC_head_tag_str),
                   1L, TEt_tag, 1, 1);

#ifdef PARSER_DEBUG_B
printf ("dict0014: 3\n");
#endif /* PARSER_DEBUG_B */
  if (lcc->LC_tail_tag_str != (char *) 0)
  tail_tag_text= hyx_mktx_elem_and_segm (hpc, lcc->LC_tail_tag_str,
                   (long) strlen (lcc->LC_tail_tag_str),
                   1L, TEt_tag, 1, 1);

#ifdef PARSER_DEBUG_B
printf ("dict0014: 4\n");
#endif /* PARSER_DEBUG_B */
  return dict_restructure_new_entry (hpc, tx_new_entry, entry_key,
                                     entry_key_size,
                                     lcc->LC_do_strip,
                                     head_tag_text, tail_tag_text);
}
