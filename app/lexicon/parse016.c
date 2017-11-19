/*
 *  FILE %lexicon/parse016.c
 *
 *  print markup structure
 *
 *  written:       1991 03 31
 *  latest update: 1996-02-18 12:53:03
 *  $Id: parse016.c,v 1.3 2004/05/08 15:40:34 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/parse.h>
#include <gg/strings.h>

#ifdef DIAGNOSTIC
#define print_text_segment_list diag_print_text_segment_list
#define display_markup diag_display_markup
#define display_text_element diag_display_text_element
#endif

/* ------------------------------------------------------------------------ */
void display_text_element (FILE *fo, struct TEXT_ELEMENT *t, char *txt, int strip)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */
  char *cl= "";

#ifdef MSDOS
  txt;
#endif

  if (t == (struct TEXT_ELEMENT *) 0) return;

  /* fprintf (fo, "%s: ", txt); */
  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    switch (t->TE_type)
    {
      case TEt_tag:             cl= "";     break;
      case TEt_declaration:     cl= "!";    break;
      case TEt_processing:      cl= "?";    break;
      default:                  cl= "";     break;
    }

#ifdef DIAGNOSTIC
    fprintf (fo, "[lev=%ld%s]", t->TE_level, cl);

    if ((td= t->TE_tag_definition) != (struct TAG_DEFINITION *) 0)
    {
      fputc ('[', fo);
      display_tag_definition (fo, td);
      fputc (']', fo);
    }
#endif /* DIAGNOSTIC */

    if (t->sig == SIG_TEXT_ELEMENT)
    {
      fprintf (fo, "<%s", cl);
      if (strip)
      {
        print_text_segment_list_stripped (fo, t->TE_text_segment);
      }
      else
      {
        print_text_segment_list (fo, t->TE_text_segment);
      }
      fprintf (fo, ">");
    }
  }

  fprintf (fo, "\n");
}

/* ------------------------------------------------------------------------ */
void display_markup (
FILE *fo,
struct HYX_PARSER_CLASS *hpc,
struct TEXT_ELEMENT *t,
int indent,
int verbosity,
int append_eoln,
int strip)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */
  struct MARKUP *m;
  int item= 0;

  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    item++;

    /**** fprintf (fo, "[sig=0x%04X]", t->sig); ****/
#ifdef DIAGNOSTIC
    if (t->sig == SIG_TEXT_ELEMENT) fprintf (fo, "(lev=%d)", t->TE_level);
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
      /*******
      fprintf (fo, "[%2d] TEXT_ELEMENT (%ld)  ", item, t->TE_level);
      *******/
      if (t->TE_level == 0)
      {
        print_text_segment_list (fo, t->TE_text_segment);
        if (append_eoln) fputc ('\n', fo);
      }
      else
      if (t->TE_level == 1)
      {
        char *cl;

        switch (t->TE_type)
        {
          case TEt_tag:             cl= "";  break;
          case TEt_declaration:     cl= "!"; break;
          case TEt_processing:      cl= "?"; break;
          default:                  cl= "";  break;
        }

        fprintf (fo, "<%s", cl);
        /**** print_text_segment_list_stripped (fo, t->TE_text_segment); ****/
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
        display_text_element (fo, (struct TEXT_ELEMENT *) m->tag_open, "Start", strip);
      }

      display_markup (fo, hpc, m->tagged_text, indent+2, verbosity, append_eoln, strip);

      if (m->tag_close != (void *) 0)
      {
        if (verbosity > 0)
        {
          blanks (fo, indent); /* ... here it's necessary to print blanks */
          display_text_element (fo, (struct TEXT_ELEMENT *) m->tag_close, "Stop ", strip);
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
