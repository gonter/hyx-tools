/*
 *  FILE %lexicon/parse008.c
 *
 *  Text Segment Liste ausgeben
 *
 *  written:       1991 03 18
 *  latest update: 1995-04-01
 *  $Id: parse008.c,v 1.3 2004/05/08 15:40:34 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/parse.h>

#ifdef DIAGNOSTIC
#define print_text_segment_list diag_print_text_segment_list
#define print_text_segment_list_stripped diag_print_text_segment_list_stripped
#endif /* DIAGNOSTIC */

/* ------------------------------------------------------------------------ */
int print_text_segment_list (FILE *fo, struct TEXT_SEGMENT *ts)
{
  long l;
  char *cp;
  int first_char= -1;

  for (;
       ts != (struct TEXT_SEGMENT *) 0;
       ts= ts->TSEG_next)
  {
    cp= ts->TSEG_text_array;
    if (first_char == -1) first_char= *cp;

#ifdef DIAGNOSTIC
    fputc ('{', fo);
#endif /* DIAGNOSTIC */

    for (l= ts->TSEG_text_lng; l > 0; l--) fputc (*cp++, fo);

#ifdef DIAGNOSTIC
    fputc ('}', fo);
#endif /* DIAGNOSTIC */
  }

  return first_char;
}

/* ------------------------------------------------------------------------ */
int print_text_segment_list_stripped (FILE *fo, struct TEXT_SEGMENT *ts)
{
  long l;
  char *cp;
  int ch;
  int first_char= -1;
/* BEGIN inserted */
  int spaces= 0;
  int do_strip= 1;   /* maybe a parameter */
  int is_space;
/* END inserted */

  for (;
       ts != (struct TEXT_SEGMENT *) 0;
       ts= ts->TSEG_next)
  {
    cp= ts->TSEG_text_array;
    if (first_char == -1) first_char= *cp;
#ifdef DIAGNOSTIC
    fputc ('{', fo);
#endif /* DIAGNOSTIC */

    for (l= ts->TSEG_text_lng; l > 0; l--)
    {
/* BEGIN inserted */
      ch= *cp++;
      is_space= (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n');

      if (is_space && do_strip)
      {
        if (!spaces) fputc (' ', fo);
        spaces++;
      }
      else
      {
        fputc (ch, fo);
        spaces= 0;
      }
/* END inserted */
    }

#ifdef DIAGNOSTIC
    fputc ('}', fo);
#endif /* DIAGNOSTIC */
  }

  return first_char;
}
