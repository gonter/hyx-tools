/*
 *  FILE %sgml/hytxt032.c
 *
 *  print markup structure
 *
 *  written:       1991 03 31
 *  latest update: 1995-08-21
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/parse.h>
#include <gg/strings.h>
#include <gg/hyx.h>
#include <gg/hytxt.h>

#ifdef DIAGNOSTIC
#define print_text_segment_list diag_print_text_segment_list
#define display_markup diag_display_markup
#endif

static char thread_name [1024];
static char frame_name [1024];

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
void hyx_thr_process (
FILE *fo,
FILE *fi_hyx,
FILE *fi_idx,
FILE *fi_lut,
FILE *fi_xfn,
int verbose_mode,
int extract_flags,
char *wanted_thread,
struct TEXT_ELEMENT *t,
int verbosity,
int append_eoln)
{
#ifdef DIAGNOSTIC
  struct TAG_DEFINITION *td;
#endif /* DIAGNOSTIC */
  struct MARKUP *m;
  int item= 0;
  struct TEXT_SEGMENT *ts;
  char *cp;

  for (; t != (struct TEXT_ELEMENT *) 0; t= t->TE_next)
  {
    item++;

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
        ts= t->TE_text_segment;
        print_text_segment_list (fo, ts);
        fputc ('>', fo);
/* fputs ("*********", fo); */
        if (ts != (struct TEXT_SEGMENT *) 0
           && (cp= ts->TSEG_text_array) != (char *) 0
           && strncmp (cp, "hyx.l ", 6) == 0
           && find_attr_value (cp, frame_name, 256, "fr") == 0
           && find_attr_value (cp, thread_name, 256, "thr") == 0
           && strcmp (thread_name, wanted_thread) == 0)
        {
          fputc ('\n', fo);
          hyx_thr_extract (fo, fi_hyx, fi_idx, fi_lut, fi_xfn, frame_name,
                           verbose_mode, extract_flags, wanted_thread);
          fputs ("\n%%", fo);
        }
        if (append_eoln) fputc ('\n', fo);
      }
    }
    else
    if (t->sig == SIG_MARKUP)
    {
      m= (struct MARKUP *) t;

      if (verbosity > 0)
      {
        xx_print (fo, (struct TEXT_ELEMENT *) m->tag_open, "Start");
      }

      hyx_thr_process (fo, fi_hyx, fi_idx, fi_lut, fi_xfn,
                       verbose_mode, extract_flags, wanted_thread,
                       m->tagged_text, verbosity, append_eoln);

      if (m->tag_close != (void *) 0)
      {
        if (verbosity > 0)
        {
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
