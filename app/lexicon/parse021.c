/*
 *  FILE ~/usr/lexicon/parse021.c
 *
 *  Text Liste ausgeben
 *
 *  written:       1994-11-16
 *  latest update: 1995-08-19
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
void dump_text_element_list (FILE *fo, struct TEXT_ELEMENT *t)
{
  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    if (t->sig == SIG_TEXT_ELEMENT)
    {
      fprintf (fo, "[%3ld", t->TE_level);
      dump_text_segment_list (fo, t->TE_text_segment);
      fputc (']', fo);
    }
  }
}
