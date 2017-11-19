/*
 *  FILE %lexicon/dictadd6.c
 *
 *  Schreiben eines Lexicon Eintrags
 *
 *  written:       1991 03 26
 *  latest update: 1996-06-09 11:06:41
 *
 */

#include <stdio.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
static int t_open=  '<';
static int t_close= '>';

/* ------------------------------------------------------------------------ */
int write_lexicon_text (FILE *fhyx, struct TEXT_ELEMENT *le, int write_nl)
{
  struct MARKUP *m;

  /* Eintrag schreiben */
  for (; le != (struct TEXT_ELEMENT *) 0; le= le->TE_next)
  {
    if (le->sig == SIG_MARKUP)
    {
      m= (struct MARKUP *) le;
      write_lexicon_text (fhyx, m->tag_open, write_nl);
      write_lexicon_text (fhyx, m->tagged_text, write_nl);
      write_lexicon_text (fhyx, m->tag_close, write_nl);
    }
    else
    if (le->sig == SIG_TEXT_ELEMENT)
    {
      if (le->TE_level == 0)
      {
        print_text_segment_list (fhyx, le->TE_text_segment);
      }
      else
      if (le->TE_level == 1)
      {
        struct TEXT_SEGMENT *txs;
        int first_char;

        if ((txs= le->TE_text_segment) != (struct TEXT_SEGMENT *) 0)
        {
          if (write_nl && txs->TSEG_text_array [0] != '/') fputc ('\n', fhyx);
          fputc (t_open, fhyx);
          first_char= print_text_segment_list (fhyx, txs);
          fputc (t_close, fhyx);
        }
      }
    }
  }

  return 0;
}
