/*
 *  FILE %usr/lexicon/parse017.c
 *
 *  Tag Definition ausgeben
 *
 *  written:       1991 03 31
 *                 1995-03-31
 *  latest update: 2001-02-18 19:32:43
 *  $Id: parse017.c,v 1.2 2001/02/19 00:27:18 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>

static char *TT [] = { "??", "rec", "nonrec", "end", "auto" } ;

/* ------------------------------------------------------------------------ */
void display_tag_definition (FILE *fo, struct TAG_DEFINITION *td)
{
  if (td->sig == SIG_TAG_DEFINITION)
  {
    fprintf (fo,
             "TAGDEF '%s' id=0x%08lX  tt=%s  w=%ld  mm=%d",
             td->tag_name,
             td->tag_id,
             TT [td->tag_type],
             td->tag_weight,
             td->match_mode);
    if (td->tag_comment != (char *) 0)
      fprintf (fo, "  cmt='%s'", td->tag_comment);
    /* fputc ('\n', fo); */
  }
}
