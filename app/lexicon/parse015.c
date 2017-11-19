/*
 *  FILE %lexicon/parse015.c
 *
 *  print markup structure
 *
 *  written:       1991 03 31
 *                 1995-08-17 (copied from display_markup)
 *  latest update: 1996-02-18  8:32:11
 *  $Id: parse015.c,v 1.2 2004/05/08 15:40:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/strings.h>

#ifdef DIAGNOSTIC
#define print_text_segment_list diag_print_text_segment_list
#define display_markup diag_display_markup
#endif

/* ------------------------------------------------------------------------ */
static void xx_print (FILE *fo, struct TEXT_ELEMENT *t, char *txt)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */

  txt;

  if (t == (struct TEXT_ELEMENT *) 0) return;

  /* fprintf (fo, "%s: ", txt); */
  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
#ifdef DIAGNOSTIC
    if ((td= t->TE_tag_definition) != (struct TAG_DEFINITION *) 0)
    {
      fputc ('[', fo);
      display_tag_definition (fo, td);
      fputc (']', fo);
    }
#endif /* DIAGNOSTIC */

    if (t->sig == SIG_TEXT_ELEMENT)
    {
      fprintf (fo, "<");
      print_text_segment_list (fo, t->TE_text_segment);
      fprintf (fo, ">");
    }
  }
  fprintf (fo, "\n");
}

/* ------------------------------------------------------------------------ */
void process_markup (
struct HYX_PARSER_CLASS *hpc,
struct OUTPUT_DESCRIPTOR *od,
struct TEXT_ELEMENT *t)
/*************
int indent,
int verbosity,
int append_eoln,
int strip
)
*************/
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */
  struct MARKUP *m;
  int item= 0;

  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    item++;

#ifdef DIAGNOSTIC
      if ((td= t->TE_tag_definition) != (struct TAG_DEFINITION *) 0)
      {
        fputc ('[', fo);
        display_tag_definition (fo, td);
        fputc (']', fo);
      }
#endif /* DIAGNOSTIC */

    blanks (fo, indent);

    if (t->sig == SIG_TEXT_ELEMENT)
    {
      /*****
      fprintf (fo, "[%2d] TEXT_ELEMENT (%ld)  ", item, t->TE_level);
      *******/
      if (t->TE_level == 0)
      {
        print_text_segment_list (fo, t->TE_text_segment);
        if (append_eoln) fputc ('\n', fo);
      } else
      if (t->TE_level == 1)
      {
        fputc ('<', fo);
        print_text_segment_list (fo, t->TE_text_segment);
        fputc ('>', fo);
        if (append_eoln) fputc ('\n', fo);
      }
    }
    else
    if (t->sig == SIG_MARKUP)
    {
      m= (struct MARKUP *) t;

      if (verbosity > 1)
      {
        /* fprintf (fo, "[%2d] MARKUP\n", item); */
        /* blanks (fo, indent); */
        /* display_tag_definition (fo, m->tag_definition); */
      }

      if (verbosity > 0)
      {
        /* blanks (fo, indent); ... erfolgt bereits weiter vorne! */
        xx_print (fo, (struct TEXT_ELEMENT *) m->tag_open, "Start");
      }

      display_markup (fo, hpc, m->tagged_text, indent+2, verbosity, append_eoln, strip);

      if (m->tag_close != (void *) 0)
      {
        if (verbosity > 0)
        {
          blanks (fo, indent); /* ... here it's necessary to print blanks */
          xx_print (fo, (struct TEXT_ELEMENT *) m->tag_close, "Stop ");
        }
      }
    }
    else
    {
      fprintf (fo, "[%2d] unknown element in list! sig=%d\n", item, t->sig);
      return;
    }
  }
}
