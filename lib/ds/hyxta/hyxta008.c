/*
 *  FILE %ds/hyxta/hyxta008.c
 *
 *  see also: %etc/lexicon.tags
 *
 *  written:       1995-03-31
 *  latest update: 1997-11-02 23:40:09
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/ta.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif /* MSDOS */

/* ------------------------------------------------------------------------ */
struct TAG_DEFINITION *hyx_ta_find_tag_definition (
struct HYX_PARSER_CLASS *hpc,
long cat_flags)
{
  if (cat_flags & TA_CATF_space)
    return hyx_find_tag_definition (hpc, "ta.space");

  if (cat_flags & TA_CATF_letter)
    return hyx_find_tag_definition (hpc, "ta.word");

  if (cat_flags & TA_CATF_digit)
    return hyx_find_tag_definition (hpc, "ta.number");

  if (cat_flags & TA_CATF_satz)
    return hyx_find_tag_definition (hpc, "ta.punkt");

  return hyx_find_tag_definition (hpc, "ta.otok");
}
