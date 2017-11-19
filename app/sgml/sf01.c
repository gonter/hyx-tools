/*
 *  FILE ~/usr/sgml/sf01.c
 *
 *  written:       1994-04-12
 *  latest update: 1995-03-25
 *
 */

#include <stdio.h>
#include <gg/hytxt.h>
#include <gg/convent.h>

#define TAG_BUFFER_SIZE 10240
static char tag_buffer [TAG_BUFFER_SIZE];

/* ------------------------------------------------------------------------ */
int hytxt_filter (FILE *fi, FILE *fo, long transfer_length,
int translit_entities)
{
#define ST_start  0
#define ST_tag    1
#define ST_entity 2
  int st= ST_start;
  int tagsiz= TAG_BUFFER_SIZE-1;/* init just to be on the safe side ...     */
  char *tagp= tag_buffer;       /* init just to be on the safe side ...     */
  char *ch_entity;              /* entity string for a character code       */
  long look_ahead= -1L;
  int ch;

  if (fi == (FILE *) 0 || fo == (FILE *) 0) return -1;

  while (transfer_length-- > 0L)
  {
    if (look_ahead == 0L) fprintf (fo, "</a>");
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;

    switch (st)
    {
      case ST_start:
        /* tag opener found */
        if (ch == '<')
        {
          tagsiz= TAG_BUFFER_SIZE-1;
          tagp= tag_buffer;
          st= ST_tag;
          break;
        }

        /* entity opener found */
        if (ch == '&')
        {
          tagsiz= TAG_BUFFER_SIZE-1;
          tagp= tag_buffer;
          st= ST_entity;
          break;
        }

        /* characters over 0x80 must be converted to entities */
        if (translit_entities
            && (ch_entity= get_pc_sgml_entity (ch)) != (char *) 0)
        {
          fputc ('&', fo);
          fputs (ch_entity, fo);
          fputc (';', fo);
        }
        else fputc (ch, fo);
        break;

      case ST_tag:
        /* processing a tagging sequence */
        if (ch == '>')
        {
          st= ST_start;
          *tagp= 0;
          look_ahead= hytxt_hyx2html (fo, tag_buffer);
          if (look_ahead == 0) look_ahead= -1L;
          if (look_ahead > 0) look_ahead++;
          break;
        }
        if (tagsiz <= 0) break;
        *tagp++= (char) ch;
        tagsiz--;
        break;

      case ST_entity:
        /* processing an entity sequence */
        if (ch == ';')
        {
          st= ST_start;
          *tagp= 0;
          fputc ('&', fo);
          fputs (tag_buffer, fo);
          fputc (';', fo);
          break;
        }
        if (tagsiz <= 0) break;
        *tagp++= (char) ch;
        tagsiz--;
        break;

      default:
        fprintf (stderr, "hytxt_filter: internal error!\n");
        return -1;
    }
    if (look_ahead >= 0L) look_ahead--;
  }

  hyx_print_relational_links (fo);

  return 0;
}
