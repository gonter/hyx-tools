/*
 *  FILE %lexicon/dict0016.c
 *
 *  print markup structure
 *
 *  written:       1995-08-19: reorganized version of display_markup
 *  latest update: 1995-08-19
 *
 */

#include <stdio.h>
#include <gg/dyb.h>
#include <gg/parse.h>
#include <gg/strings.h>

#ifdef DIAGNOSTIC
#define hyx_unroll_text_segment_list hyx_idag_unrtxtsl
#define hyx_unroll_text              hyx_diag_unrtxt
#endif

/* ------------------------------------------------------------------------ */
static void xx_unroll (
struct DYNAMIC_BLOCK *dyb,
struct TEXT_ELEMENT *t,
char *txt)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */

#ifdef MSDOS
  txt;
#endif

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
      dyb_append_block (dyb, "<", 1L);
      hyx_unroll_text_segment_list (dyb, t->TE_text_segment);
      dyb_append_block (dyb, ">", 1L);
    }
  }

  dyb_append_block (dyb, "\n", 1L);
}

/* ------------------------------------------------------------------------ */
int hyx_unroll_text (
struct DYNAMIC_BLOCK *dyb,
struct TEXT_ELEMENT *t,
int indent,
int verbosity,
int append_eoln)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */
  struct MARKUP *m;
  int item= 0;

  if (dyb == (struct DYNAMIC_BLOCK *) 0
      || t == (struct TEXT_ELEMENT *) 0
     ) return -1;

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

    dyb_append_blanks (dyb, (long) indent);

    if (t->sig == SIG_TEXT_ELEMENT)
    {
      /*******
      fprintf (fo, "[%2d] TEXT_ELEMENT (%ld)  ", item, t->TE_level);
      *******/
      if (t->TE_level == 0)
      {
        hyx_unroll_text_segment_list (dyb, t->TE_text_segment);
        if (append_eoln) dyb_append_block (dyb, "\n", 1L);
      } else
      if (t->TE_level == 1)
      {
        dyb_append_block (dyb, "<", 1L);
        hyx_unroll_text_segment_list (dyb, t->TE_text_segment);
        dyb_append_block (dyb, ">", 1L);
        if (append_eoln) dyb_append_block (dyb, "\n", 1L);
      }
    }
    else
    if (t->sig == SIG_MARKUP)
    {
      m= (struct MARKUP *) t;

      if (verbosity > 1)
      {
        /* fprintf (fo, "[%2d] MARKUP\n", item); */
        /* dyb_append_blanks (dyb, (long) indent); */
        /* display_tag_definition (fo, m->tag_definition); */
      }

      if (verbosity > 0)
      {
        /* dyb_append_blanks (dyb, (long) indent);      */
        /*  ... erfolgt bereits weiter vorne!           */
        xx_unroll (dyb, (struct TEXT_ELEMENT *) m->tag_open, "Start");
      }

      hyx_unroll_text (dyb, m->tagged_text, indent+2, verbosity, append_eoln);

      if (m->tag_close != (void *) 0)
      {
        if (verbosity > 0)
        {
          /* ... here it's necessary to print blanks: */
          dyb_append_blanks (dyb, (long) indent);
          xx_unroll (dyb, (struct TEXT_ELEMENT *) m->tag_close, "Stop ");
        }
      }
    }
    else
    {
      fprintf (stderr,
               "[%2d] unknown element in list! sig=%d\n", item, t->sig);
      return -1;
    }
  }

  return 0;
}
