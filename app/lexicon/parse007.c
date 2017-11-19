/*
 *  FILE %usr/lexicon/parse007.c
 *
 *  Text Liste ausgeben
 *
 *  written:       1991 03 18
 *  latest update: 2001-02-18 18:38:01
 *  $Id: parse007.c,v 1.2 2001/02/19 00:27:18 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
void print_text_element_list (FILE *fo, struct TEXT_ELEMENT *t)
{
  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    if (t->sig == SIG_TEXT_ELEMENT)
    {
      fprintf (fo, "level=%3ld, type=%3ld def=0x%08lX: ",
               t->TE_level, t->TE_type, t->TE_tag_definition);
      print_text_segment_list (fo, t->TE_text_segment);
      fputc ('\n', fo);
    }
  }
}
