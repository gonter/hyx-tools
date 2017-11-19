/*
 *  FILE %lexicon/dict0002.c
 *
 *  written:       1994-07-29
 *  latest update: 1999-05-08 10:41:57
 *  $Id: dict0002.c,v 1.3 2001/02/19 00:27:16 gonter Exp $
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
int dict_check_integrity (struct HYX_PARSER_CLASS *hpc)
{
  if ((hyx_find_tag_definition (hpc, "LE") == (struct TAG_DEFINITION *) 0
   &&hyx_make_tag_definition (hpc, "LE", 0x0201L, 0, 5000L, 2, "lexicon entry begin")
     == (struct TAG_DEFINITION *) 0)
  || (hyx_find_tag_definition (hpc, "/LE") == (struct TAG_DEFINITION *) 0
   &&hyx_make_tag_definition (hpc, "/LE", 0x0202L, 0, 5000L, 3, "lexicon entry end")
     == (struct TAG_DEFINITION *) 0)
  || (hyx_find_tag_definition (hpc, ":") == (struct TAG_DEFINITION *) 0
   &&hyx_make_tag_definition (hpc, ":", 0x0001L, 1, 10000L, 2, "frame begin")
     == (struct TAG_DEFINITION *) 0)
  || (hyx_find_tag_definition (hpc, ";") == (struct TAG_DEFINITION *) 0
   &&hyx_make_tag_definition (hpc, ";", 0x0002L, 1, 10000L, 3, "frame end")
     == (struct TAG_DEFINITION *) 0))
   return -1;

  return 0;
}
