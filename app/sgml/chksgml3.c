/*
 *  FILE %sgml/chksgml3.c
 *
 *  check a SGML file stream
 *
 *  this module is stateless
 *
 *  written:       1991 07 14
 *                 1992 12 07: revision; extra buffers
 *                 1993-01-03: entity lookup via code table
 *                 1994-12-10: isolated from chksgml2.c
 *  latest update: 1996-10-13 11:25:27
 *
 */

#include <stdio.h>
#include <string.h>
#define USE_CODE_TABLE
#ifdef  USE_CODE_TABLE
#include <gg/codes.h>
#endif
#include <gg/strings.h>
#include <gg/convent.h>
#include <gg/filename.h>
#include <gg/hytxt.h>

#define LEVEL_WARNING (verbose_level > 1)

/* various STATES of the chksgml scanner */
#define STAT_start              0
#define STAT_tag                1
#define STAT_entity             2
#define STAT_tag_entity         3
#define STAT_tag_begin          4
#define STAT_declaration        5

/* ------------------------------------------------------------------------ */
#define ENTITY_PUFFER_SIZE 32
static long MAX_ENTITY_SIZE= 16L;
static char entity_puffer [ENTITY_PUFFER_SIZE];
static int entity_idx= 0;

#define TAG_PUFFER_SIZE 1024
static long MAX_TAG_SIZE= 1024L;
static char tag_puffer [TAG_PUFFER_SIZE];
static char frame_name_puffer [TAG_PUFFER_SIZE];
static int tag_idx= 1;

static struct HYX_OBJECT_COUNTER
  *tag_counter=    (struct HYX_OBJECT_COUNTER *) 0,
  *entity_counter= (struct HYX_OBJECT_COUNTER *) 0;

/* ------------------------------------------------------------------------ */
int chksgml_stream (
FILE *fo,
FILE *fo_report,
FILE *fi,
char *fn,
int verbose_level,
long byte_offset,
long byte_count,
int flags)
{
  int ch;
  int ch2;
  int state= STAT_start;                /* possible STATES of the engine    */
  int rc;
  long off= 0L;
  long tag_open_off= 0L;
  long entity_open_off= 0L;
  long linenr= 1L;
  long open_linenr= 0L;
  long cnt_warning= 0L;
  long cnt_error= 0L;
  long cnt_entity= 0L;
  long cnt_tag= 0L;
  long cnt_tag_entity= 0L;
  long cnt_hyx_err= 0L;
  int flg_hyx= 0;
  int watch_entity= 0;
  int watch_tag= 0;
  int tag_code;
  long frame_line= 0L;                  /* line number within frame         */
  int frame_column= 0;
  int frame_state= 0;                   /* frame open or closed             */
  int in_frame= 0;
  int nesting_level= 0;                 /* number of nested decl. structs.  */

  frame_name_puffer [0]= 0;

  for (off= byte_offset; byte_count-- > 0L; off++)
  {
    ch= fgetc (fi) & 0x00FF;
    if (feof (fi)) break;

    switch (state)
    {
      case STAT_start:
        open_linenr= linenr;
        switch (ch)
        {
          case '&':
            state= STAT_entity;
            cnt_entity++;
            watch_entity= 1;
            entity_idx= 0;
            entity_open_off= off;
            break;

          case '<':
            state= STAT_tag_begin;
            cnt_tag++;
            watch_tag= 1;
            tag_idx= 0;
            tag_open_off= off;
            break;

          case '>':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag close in normal text!\n",
              off, linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            cnt_error++;
            break;

          default:
PLAIN_TEXT:
            if (fo != (FILE *) 0) fputc (ch, fo);
            if (ch == 0x0A)
            {
              frame_column= 0;
              frame_line++;
            } else frame_column++;
            break;
        }
        break;

      case STAT_entity:
        switch (ch)
        {
          case ';':
            state= STAT_start;
            rc= analyze_entity (entity_puffer, 1, &entity_counter);
#ifdef USE_CODE_TABLE
            ch2= find_sgml_entity (entity_puffer);
#else
            ch2= find_pc_sgml_entity (entity_puffer);
            if (ch2 == -1) ch2= find_typographic_sgml_entity (entity_puffer);
#endif
            if (ch2 == -1)
            {
              if (rc == 0 && LEVEL_WARNING)
              {
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: unknown ENTITY \'%s\'!\n",
                  entity_open_off, open_linenr, entity_puffer);
                if (frame_name_puffer [0] != 0)
                  fprintf (fo_report,
                    "  frame_line=%ld frame='%s'\n",
                    frame_line, frame_name_puffer);
              }
              cnt_warning++;
            }
            else
            {
              if (fo != (FILE *) 0) fputc (ch2, fo);
              frame_column++;
            }
            break;

          case '<':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag open within ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            state= STAT_tag;
            cnt_error++;
            break;

          case '>':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag close within ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            state= STAT_start;
            cnt_error++;
            break;

          case '&':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: entity open within ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            cnt_error++;
            break;

          case 0x0A:
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: new line within ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            cnt_error++;
            state= STAT_start;
            break;

          default:
            if (entity_idx == 0
                && !((ch >= 'A' && ch <= 'Z')
                     || (ch >= 'a' && ch <= 'z')
                     || ch == '#'       /* &#number;                        */
                     || ch == '('       /* &(name,name)name; is possible    */
                    )
               )
            { /* ERO-Char not followed by a name start character */
              state= STAT_start;
              if (fo != (FILE *) 0) fputc ('&', fo);
              goto PLAIN_TEXT;
            }

            if (off - entity_open_off > MAX_ENTITY_SIZE && watch_entity)
            {
              if (LEVEL_WARNING)
              {
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: ENTITY longer than %ld bytes!\n",
                  entity_open_off, open_linenr, MAX_ENTITY_SIZE);
                if (frame_name_puffer [0] != 0)
                  fprintf (fo_report,
                    "  frame_line=%ld frame='%s'\n",
                    frame_line, frame_name_puffer);
              }
              cnt_warning++;
              watch_entity= 0;
            }

            if (entity_idx+1 < ENTITY_PUFFER_SIZE)
            {
              entity_puffer [entity_idx++]= (char) ch;
              entity_puffer [entity_idx]= 0;
            }
            break;
        }
        break;

      case STAT_tag_begin:
        switch (ch)
        {
          case '!':
            fprintf (fo_report, "NOTE: declaration start\n");
            nesting_level= 1;
            state= STAT_declaration;
            if (LEVEL_WARNING)
            {
              fprintf (fo_report,
"- off=0x%08lX line=%5ld: NOTE: nesting level %d\n",
                      tag_open_off, open_linenr, nesting_level);
            }
            break;
          default:
            state= STAT_tag;
            goto _STAT_tag;
        }
        break;

      case STAT_tag:
_STAT_tag:
        switch (ch)
        {
          case '<':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag open within TAG!\n",
              tag_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            state= STAT_tag;
            cnt_error++;
            break;

          case '>':
            state= STAT_start;
            if (flags & CHKSGML_Fign_case) to_lower (tag_puffer);
            rc= analyze_tag (tag_puffer, &tag_code, &tag_counter, &frame_state);
            switch (rc)
            {
              case 1:
                flg_hyx= 1;
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: 2 <Frame ...> without </Frame>!\n",
                  tag_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
                cnt_hyx_err++;
                break;
              case 2:
                flg_hyx= 1;
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: 2 </Frame> without <Frame ...>!\n",
                  tag_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
                cnt_hyx_err++;
                break;
              case 3:
                flg_hyx= 1;
                break;
            }

            switch (tag_code)
            {
              case TAGo_Frame:
              case TAGso_Frame:
                strcpy (frame_name_puffer, tag_puffer);
                frame_line= 1L;
                frame_column= 0;
                in_frame= 1;
                break;
            }
            break;

          case 0x0A:
            if (LEVEL_WARNING)
            {
              fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: new line within tag! (open in line=%ld)\n",
                tag_open_off, linenr, open_linenr);
              if (frame_name_puffer [0] != 0)
                fprintf (fo_report,
                  "  frame_line=%ld frame='%s'\n",
                  frame_line, frame_name_puffer);
            }
            cnt_warning++;
            ch= ' ';
            linenr++;
            goto STAT_TAG_default;
            break;

          case '&':
            state= STAT_tag_entity;
            cnt_tag_entity++;
            watch_entity= 1;
            entity_idx= 0;
            entity_open_off= off;

          default:
STAT_TAG_default:
            if (off-tag_open_off > MAX_TAG_SIZE && watch_tag)
            {
              if (LEVEL_WARNING)
              {
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: TAG longer than %ld bytes!\n",
                  tag_open_off, open_linenr, MAX_TAG_SIZE);
                if (frame_name_puffer [0] != 0)
                  fprintf (fo_report,
                    "  frame_line=%ld frame='%s'\n",
                    frame_line, frame_name_puffer);
              }
              cnt_warning++;
              watch_tag= 0;
            }
            if (tag_idx+1 < TAG_PUFFER_SIZE)
            {
              tag_puffer [tag_idx++]= (char) ch;
              tag_puffer [tag_idx]= 0;
            }
            break;
        }
        break;

      case STAT_tag_entity:
        switch (ch)
        {
          case ';':
          case '.':
            state= STAT_tag;
            rc= analyze_entity (entity_puffer, 2, &entity_counter);

#ifdef USE_CODE_TABLE
            ch2= find_sgml_entity (entity_puffer);
#else
            ch2= find_pc_sgml_entity (entity_puffer);
            if (ch2 == -1) ch2= find_typographic_sgml_entity (entity_puffer);
#endif

            if (ch2 == -1)
            {
              if (rc == 0 && LEVEL_WARNING)
              {
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: unknown ENTITY (within tag) \'%s\'!\n",
                  entity_open_off, open_linenr, entity_puffer);
                if (frame_name_puffer [0] != 0)
                  fprintf (fo_report,
                    "  frame_line=%ld frame='%s'\n",
                    frame_line, frame_name_puffer);
              }
              cnt_warning++;
            }
            goto STAT_TAG_default; /* store data in tag too */

          case '<':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag open within TAG-ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            state= STAT_tag;
            cnt_error++;
            break;

          case '>':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: tag close within TAG-ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            state= STAT_start;
            cnt_error++;
            break;

          case '&':
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: entity open within TAG-ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            cnt_error++;
            break;

          case 0x0A:
            fprintf (fo_report,
"- off=0x%08lX line=%5ld: ERROR: new line within TAG-ENTITY!\n",
              entity_open_off, open_linenr);
            if (frame_name_puffer [0] != 0)
              fprintf (fo_report,
                "  frame_line=%ld frame='%s'\n",
                frame_line, frame_name_puffer);
            cnt_error++;
            break;

          default:
            if (off-entity_open_off > MAX_ENTITY_SIZE && watch_entity)
            {
              if (LEVEL_WARNING)
              {
                fprintf (fo_report,
"- off=0x%08lX line=%5ld: WARNING: TAG-ENTITY longer than %ld bytes!\n",
                  entity_open_off, open_linenr, MAX_ENTITY_SIZE);
                if (frame_name_puffer [0] != 0)
                  fprintf (fo_report,
                    "  frame_line=%ld frame='%s'\n",
                    frame_line, frame_name_puffer);
              }
              cnt_warning++;
              watch_entity= 0;
            }
            if (entity_idx+1 < ENTITY_PUFFER_SIZE)
            {
              entity_puffer [entity_idx++]= (char) ch;
              entity_puffer [entity_idx]= 0;
            }
            goto STAT_TAG_default; /* store data in tag too */
        }
        break;

      case STAT_declaration:
        switch (ch)
        {
          case '<':
            nesting_level++;
            if (LEVEL_WARNING)
            {
             fprintf (fo_report,
"- off=0x%08lX line=%5ld: NOTE: nesting level %d\n",
                      tag_open_off, open_linenr, nesting_level);
            }
            break;
          case '>':
            nesting_level--;
            if (LEVEL_WARNING)
            {
             fprintf (fo_report,
"- off=0x%08lX line=%5ld: NOTE: nesting level %d\n",
                      tag_open_off, open_linenr, nesting_level);
            }
            break;
        }
        if (nesting_level <= 0) state= STAT_start;
        break;

      default:
        fprintf (fo_report,"- internal error: state=%d\n", state);
        return -1;
    }
    if (ch == 0x0A) linenr++;
  }

  switch (state)
  {
    case STAT_start:
      if (verbose_level > 0)
        fprintf (fo_report,
          "- off=0x%08lX line=%5ld: EOF: parser state OK!\n",
          off, linenr);
      break;

    case STAT_entity:
      cnt_error++;
      fprintf (fo_report,
        "- off=0x%08lX line=%5ld: EOF: error: parser state: entity open\n",
        off, linenr);
      break;

    case STAT_tag_entity:
      cnt_error++;
      fprintf (fo_report,
"- off=0x%08lX line=%5ld: EOF: error: parser state: entity open\n",
off, linenr);

    case STAT_tag:
      cnt_error++;
      fprintf (fo_report,
"- off=0x%08lX line=%5ld: EOF: error: parser state: tagging sequence open\n",
off, linenr);
      break;

    default:
      cnt_error++;
      fprintf (fo_report,
"- off=0x%08lX line=%5ld: EOF: error: parser state=%d\n", off, linenr, state);
      break;
  }

  if (verbose_level > 0)
  {
    hoc_print_counter (fo_report, tag_counter, 1);
    hoc_print_counter (fo_report, entity_counter, 2);

    fprintf (fo_report, "-- %ld entities\n", cnt_entity);
    fprintf (fo_report, "-- %ld tags\n", cnt_tag);
    fprintf (fo_report, "-- %ld entities within tags\n", cnt_tag_entity);
    fprintf (fo_report, "-- %ld warnings\n", cnt_warning);
    if (flg_hyx)
    {
      fprintf (fo_report, "--- hypertext structure detected\n");
      fprintf (fo_report, "--- %ld hypertext errors\n", cnt_hyx_err);
    }
    fprintf (fo_report, "-- %ld errors\n", cnt_error);
  }

  if (verbose_level >= 0)
  {
    fprintf (fo_report,"** SUMMARY ** %s: ", fn);
    if (cnt_error > 0L) fprintf (fo_report,"SGML not ok!\n");
    else
    {
      fputs ("SGML ok!", fo_report);
      if (flg_hyx)
           if (cnt_hyx_err)
                fprintf (fo_report, " Hypertext structure not ok!\n");
           else fprintf (fo_report, " Hypertext structure ok!\n");
      else fputc ('\n', fo_report);
    }
  }

  hoc_reset_counter (tag_counter);
  hoc_reset_counter (entity_counter);

  return (cnt_error > 0L) ? 1 : 0;
}

/* ------------------------------------------------------------------------ */
int chksgml_print_total_counter (FILE *fo)
{
  hoc_print_counter (fo, tag_counter, 3);
  hoc_print_counter (fo, entity_counter, 4);

  return 0;
}
