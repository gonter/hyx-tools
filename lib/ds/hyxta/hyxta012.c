/*
 *  FILE %ds/hyxta/hyxta012.c
 *
 *  written:       1994-03-25
 *  latest update: 1997-11-02 17:16:32
 *
 */

#include <stdio.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/hytxt.h>
#include <gg/dirty.h>
#include <gg/attlist.h>
#include <gg/parse.h>
#include <gg/ta.h>

/* ------------------------------------------------------------------------ */
static int frame_is_open= 0;
static long frame_counter= 0L;
static long par_counter= 0L;
static char frame_name [82];
static char frame_name_prev [82];

struct ATTRIBUTE_LIST *al= (struct ATTRIBUTE_LIST *) 0;

/* ------------------------------------------------------------------------ */
static char *PAR_TYPE [N_PAR_TYPE] =
{
/* PAR_TYPE_text         */     "par",
/* PAR_TYPE_section_head */     "par.sec",
/* PAR_TYPE_table_head   */     "par.tbl",
/* PAR_TYPE_figure_head  */     "par.fig",
/* PAR_TYPE_chapter      */     "par.chap"
} ;

/* ------------------------------------------------------------------------ */
int ta_print_paragraph (FILE *fo, struct TEXT_ELEMENT *li, long ncnt)
{
  int par_type;
  int rv= 0;
  int prev= 0;

  if (li == (struct TEXT_ELEMENT *) 0) return 0;

fprintf (stderr, "ta_print_paragraph\n");
  par_type= ta_identify_par_type (li);
  if (par_type >= N_PAR_TYPE) par_type= PAR_TYPE_text;

  if (par_type > 0 || !frame_is_open)
    sprintf (frame_name, "fr%05ld.ta", ++frame_counter);

  if (par_type > 0 && frame_is_open)
  {
    fprintf (fo, "<hyx.l dir=next fr=\"%s\">", frame_name);
    fprintf (fo, "</Frame>\n");
    frame_is_open= 0;
    prev= 1;
  }

  if (!frame_is_open)
  {
    fprintf (fo, "<Frame %s>\n", frame_name);
    fprintf (fo, "<hyx.l dir=up fr=\"$$root\">");
    if (prev == 1)
      fprintf (fo, "<hyx.l dir=prev fr=\"%s\">", frame_name_prev);
    strcpy (frame_name_prev, frame_name);
    frame_is_open= 1;
    al_set_attribute (&al, strdup ("frame_name"), strdup (frame_name),
                      (long) ALty_opaque, (void *) li);
    rv= 1;
  }

  ta_print_nodelist (fo, li, ncnt, par_type);

  return rv;
}

/* ------------------------------------------------------------------------ */
int ta_print_nodelist (
FILE *fo,
struct TEXT_ELEMENT *li,
long ncnt,
int par_type)
{
  fprintf (fo, "<ta.%s id=%ld ncnt=%ld>",
    PAR_TYPE [par_type], ++par_counter, ncnt);

  for (; li != (struct TEXT_ELEMENT *) 0; li= li->TE_next)
    hyx_ta_print_text_segments (fo, li->TE_text_segment);

  fprintf (fo, "</ta.%s>", PAR_TYPE [par_type]);
  return 0;
}

/* ------------------------------------------------------------------------ */
int ta_identify_par_type (struct TEXT_ELEMENT *li)
{
#define beg_undef -1
  int beg= beg_undef;
  int lines= 0;

  for (; li != (struct TEXT_ELEMENT *) 0; li= li->TE_next)
  {
    if (li->TE_cat_flags & TA_CATF_space2) lines++;
    if (li->TE_cat_flags & TA_CATF_space) continue;

    if (beg == beg_undef)
    {
      if (li->TE_cat_flags & TA_CATF_digit) beg= PAR_TYPE_section_head;
      if (li->TE_cat_flags & TA_CATF_letter)
      {
        struct TEXT_SEGMENT *ts;
        char *ts_data;

        ts= li->TE_text_segment;
        ts_data= ts->TSEG_text_array;

        if (strncmp (ts_data, "Chapter", 7) == 0
           ||strncmp (ts_data, "CHAPTER", 7) == 0
           ||strncmp (ts_data, "chapter", 7) == 0) beg= PAR_TYPE_chapter;
        else
        if (strncmp (ts_data, "Table", 5) == 0
           ||strncmp (ts_data, "TABLE", 5) == 0
           ||strncmp (ts_data, "table", 5) == 0) beg= PAR_TYPE_table_head;
        else
        if (strncmp (ts_data, "Fig", 3) == 0
           ||strncmp (ts_data, "fig", 5) == 0
           ||strncmp (ts_data, "FIG", 5) == 0) beg= PAR_TYPE_figure_head;
        else
        if (strncmp (ts_data, "App", 3) == 0
           ||strncmp (ts_data, "app", 5) == 0
           ||strncmp (ts_data, "APP", 5) == 0) beg= PAR_TYPE_section_head;
        else
          beg= PAR_TYPE_text;
      }
    }
  }

  if (lines > 3) return PAR_TYPE_text;
  if (beg >= 0) return beg;

  return PAR_TYPE_text;
}

/* ------------------------------------------------------------------------ */
int ta012_finish (FILE *fo)
{
  if (frame_is_open)
  {
    fprintf (fo, "</Frame>\n");
    frame_is_open= 0;
  }
  return 0;
}

/* ------------------------------------------------------------------------ */
int ta_print_toc (FILE *fo, char *frame_name)
{
  struct ATTRIBUTE_LIST *al2;
  struct TEXT_ELEMENT *li;

  fprintf (fo, "<Frame %s>\n", frame_name);

  for (al2= al;
       al2 != (struct ATTRIBUTE_LIST *) 0;
       al2= al2->AL_next)
  {
    printf ("<hyx.l fr=\"%s\">* ", al2->AL_name);

    li= (struct TEXT_ELEMENT *) al2->AL_value;
    for (; li != (struct TEXT_ELEMENT *) 0; li= li->TE_next)
      hyx_ta_print_text_segments (fo, li->TE_text_segment);

    fputc ('\n', fo);
  }
  fprintf (fo, "</Frame>\n");

  return 0;
}
