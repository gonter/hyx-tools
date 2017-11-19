/*
 *  FILE %ds/hyxp/hyxp0002.c
 *
 *  Parse SGML sequences and generate attributed text segments.
 *  The attribute of a segment contains the text level, incremented
 *  or decremented by the '<' and '>' metacharacters respectively.
 *  level 0: normal text
 *  level 1: SGML sequence
 *  Other levels are used in declarations, not handled currently
 *
 *  For details about the operation and the future direction
 *  see struct HYX_PARSER_STATUS and the notes about ongoing
 *  ongoing restructuring of the parser.
 *
 *  written:       1991-03-12
 *  latest update: 1996-02-26  0:53:06
 *  $Id: hyxp0002.c,v 1.4 2004/05/08 15:40:18 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/parse.h>

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* states: ---------------------------------------------------------------- */
#define HPSst_start                     0
#define HPSst_markup_open               1
#define HPSst_markup_declaration        2
#define HPSst_markup_element            3
#define HPSst_markup_element_quoted     4
#define HPSst_processing_instruction    5
#define HPSst_minimized_text            6
#define HPSst_markup_open2              7
#define HPSst_md_c1                     8  /* first comment char in decl. */
#define HPSst_md_c2                     9  /* first comment char in decl. */
#define HPSst_md_c3                    10  /* first comment char in decl. */

/* #define PARSER_DEBUG 1 */

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_parse_char (
struct HYX_PARSER_STATUS *lps,
int ch)
{
  struct TEXT_ELEMENT *tt= (struct TEXT_ELEMENT *) 0;
  struct HYX_PARSER_CLASS *hpc;
  int is_minimization_begin= 0;
  int is_minimization_end= 0;
  int segment_finished= 0;

#ifdef PARSER_DEBUG
  if (PARSER_DEBUG >= 0)
  {
    /**** printf ("BEGIN hyxp0002.c SGML parser\n"); ****/
    printf ("state=%d ch=0x%02X '%c'\n",
            lps->HPS_state, ch, (ch >= 0x20) ? ch : '.');
  }
#endif /* PARSER_DEBUG */

  hpc= lps->HPS_hpc;

  switch (lps->HPS_state)
  {
    case HPSst_start:
      if (ch == hpc->HPC_tag_open)
      {
        /**************
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        lps->HPS_parser_level++;
        **************/
        lps->HPS_state= HPSst_markup_open;
      }
      else
      {
        hyx_parser_add_char (lps, ch);
      }
      break;

    case HPSst_markup_open:
      if (ch == hpc->HPC_declaration_start)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        lps->HPS_parser_level++;

        lps->HPS_element_type= TEt_declaration;
        lps->HPS_state= HPSst_markup_declaration;
      }
      else
      if (ch == hpc->HPC_processing_start)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        lps->HPS_parser_level++;

        lps->HPS_element_type= TEt_processing;
        lps->HPS_state= HPSst_processing_instruction;
      }
      else
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
      { /* not a tag begin according to the standard */
        hyx_parser_add_char (lps, '<');
        hyx_parser_add_char (lps, ch);
        lps->HPS_state= HPSst_start;
        /* lps->HPS_parser_level--; */
      }
      else
      if ((ch >= 'A' && ch <= 'Z')
          || (ch >= 'a' && ch <= 'z')
          || ch == '/'                  /* markup close                     */
          || ch == '-'                  /* !! uncorrect comment             */
          || ch == ':' || ch == ';'     /* !! HYX                           */
         )
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        lps->HPS_parser_level++;

        lps->HPS_state= HPSst_markup_element;
        lps->HPS_element_type= TEt_tag;
        hyx_parser_add_char (lps, ch);
      }
      else
      {
        /* T2D: ERROR */
      }
      break;

    case HPSst_markup_open2:
      if (ch == hpc->HPC_declaration_start)
      {
        lps->HPS_element_type= TEt_declaration;
        lps->HPS_state= HPSst_markup_declaration;
      }
      else
      if (ch == hpc->HPC_processing_start)
      {
        lps->HPS_element_type= TEt_processing;
        lps->HPS_state= HPSst_processing_instruction;
      }
      else
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
      { /* not a tag begin according to the standard */
        hyx_parser_add_char (lps, '<');
        hyx_parser_add_char (lps, ch);
        lps->HPS_state= HPSst_start;
        /* lps->HPS_parser_level--; */
      }
      else
      if ((ch >= 'A' && ch <= 'Z')
          || (ch >= 'a' && ch <= 'z')
          || ch == '/'                  /* markup close                     */
          || ch == '-'                  /* !! uncorrect comment             */
          || ch == ':' || ch == ';'     /* !! HYX                           */
         )
      {
        lps->HPS_state= HPSst_markup_element;
        lps->HPS_element_type= TEt_tag;
        hyx_parser_add_char (lps, ch);
      }
      else
      {
        /* T2D: ERROR */
      }
      break;

    case HPSst_markup_element:  /* characters of a tag name */
      if (ch == hpc->HPC_tag_open)
      { /* T2D: minimzation!!!! */
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        lps->HPS_state= HPSst_markup_open2;
      }
      else
      if (ch == hpc->HPC_tag_close)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        /* T2D: drop back context */
        lps->HPS_state= HPSst_start;
        lps->HPS_parser_level--;
      }
      else
      if (ch == hpc->HPC_minimization_char)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        /* T2D: drop back context */
        lps->HPS_state= HPSst_minimized_text;
        lps->HPS_parser_level--;
      }
      else
      if (ch == '\"' || ch == '\'')
      {
        hyx_parser_add_char (lps, ch);
        lps->HPS_state= HPSst_markup_element_quoted;
        lps->HPS_other_quote= ch;
      }
      else
      {
        hyx_parser_add_char (lps, ch);
      }
      break;

    case HPSst_markup_element_quoted:
      if (ch == lps->HPS_other_quote)
      {
        hyx_parser_add_char (lps, ch);
        lps->HPS_state= HPSst_markup_element;
      }
      else
      {
        hyx_parser_add_char (lps, ch);
      }
      break;

    case HPSst_markup_declaration:      /* not OK */
      if (ch == hpc->HPC_tag_close)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        /* T2D: drop back context */
        lps->HPS_state= HPSst_start;
        lps->HPS_parser_level--;
      }
      else
      {
        if (ch == '-')  /* T2D: formalize! */
        {
          lps->HPS_state= HPSst_md_c1;
        }
        hyx_parser_add_char (lps, ch);
      }
      break;

    case HPSst_md_c1:
      hyx_parser_add_char (lps, ch);
      lps->HPS_state= (ch == '-') ? HPSst_md_c2 : HPSst_markup_declaration;
      break;

    case HPSst_md_c2:
      hyx_parser_add_char (lps, ch);
      if (ch == '-')  /* T2D: formalize! */
      {
        lps->HPS_state= HPSst_md_c3;
      }
      break;

    case HPSst_md_c3:
      hyx_parser_add_char (lps, ch);
      lps->HPS_state= (ch == '-') ? HPSst_markup_declaration : HPSst_md_c2;
      break;

    case HPSst_processing_instruction:  /* OK */
      if (ch == hpc->HPC_tag_close)
      {
        tt= hyx_parser_finish (lps);
        segment_finished= 1;
        /* T2D: drop back context */
        lps->HPS_state= HPSst_start;
        lps->HPS_parser_level--;
      }
      else
      {
        hyx_parser_add_char (lps, ch);
      }
      break;

    case HPSst_minimized_text:
      if (ch == hpc->HPC_minimization_char)
      {
        tt= hyx_parser_finish (lps);

        lps->HPS_state= HPSst_markup_element;
        lps->HPS_element_type= TEt_tag;
        lps->HPS_parser_level++;
        hyx_parser_add_char (lps, '/');
        tt= hyx_parser_finish (lps);

        lps->HPS_parser_level--;
        segment_finished= 1;
        lps->HPS_state= HPSst_start;
      }
      else
      {
        hyx_parser_add_char (lps, ch);
      }
      break;

    default:
      fprintf (stderr, "internal error, state not know! %d\n",
               lps->HPS_state);
      break;
  }

#ifdef PARSER_DEBUG
if (segment_finished)
{
  printf (">>>>>>>>>\n");
diag_display_markup (stdout, hpc, lps->HPS_tx_list, 0, 0, 0);
printf ("\n<<<<<<<<<\n");
}
#endif /* PARSER_DEBUG */

  return tt;
}
