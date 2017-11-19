/*
 *  FILE %ned/08/ned0828.c
 *
 *  Identifizieren eines SGML Tags oder einer Entity
 *
 *  written:       1991 07 01
 *                 1991 10 30: get external tag setup information
 *  latest update: 1997-08-03 22:10:29
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"
#include <gg/convent.h>
#include <gg/strings.h>
#include <gg/window.h>
#include <gg/hyx.h>
#include <gg/dpp.h>

#define ATTR_VALUE_SIZE 60
static char attr_value [ATTR_VALUE_SIZE];

extern struct SGML_TAG_DESCRIPTOR _STD_NULL;
extern struct SGML_TAG_DESCRIPTOR _STD_PSEUDO;
extern int COL_FRAME_TAGS;
extern int COL_UNKNOWN_FEATURE;
extern int CHR_UNKNOWN_FEATURE;

/* ------------------------------------------------------------------------ */
void copy_tag (
char *dst,
char *src,
int max_dst,
int mode)
{
  int ch;

  if (max_dst < 3) goto STOP;

  *dst++ = '<';
  max_dst--;
  while (--max_dst > 1)
  {
    if ((ch= *src++ & 0x00FF) == 0) break;

    if (mode == STD_display_tag_name
        && (ch == ' ' || ch == '\t' || ch == 0x0A || ch == 0x0D)
       ) break;

    *dst++= (char) ch;
  }

  *dst++ = '>';
STOP:
  *dst = 0;

  return;
}

/* ------------------------------------------------------------------------ */
int ned_identify_feature (
struct WINDOWCTRL *wc,          /* window where all that happens            */
struct LINE *lp,                /* line to which feature is attached        */
int offset,                     /* offset in line where                     */
int feature_type,               /* general class, such as Ftype_SGML_TAG    */
struct FEATURE *ft,             /* feature to be identified                 */
char *lin,                      /* buffer containing feature to identify    */
char *repl_array,               /* buffer to place replacement code into    */
int *repl_size,                 /* used space in that buffer                */
int repl_max)                   /* maximum size of that buffer              */
/* Return: -1 .. error;  0 .. ok;  1 .. feature not needed (but defined)    */
{
  int ev;
  struct SGML_TAG_DESCRIPTOR *tag_desc= (struct SGML_TAG_DESCRIPTOR *) 0;
  int f_builtin_dispopt= 0;     /* flag to indicate built in display option */
  int f_entity_valid;

  if (repl_max <= 0 || ft == (struct FEATURE *) 0) return -1;

  *repl_size= 0;
  ft->ftr_colour= COL_DEF_FEATURE;
  ft->ftr_display_mode= FTR_display_point;
  ft->ftr_duplication= FTR_dup_allways;
  ft->ftr_replarray_size= 1;

  switch (feature_type)
  {
    case Ftype_SGML_ENTITY:
      ev= find_pc_sgml_entity (lin);
      f_entity_valid= (ev >= 0x00 && ev <= 0xFF);
      ft->ftr_colour= (f_entity_valid)
                      ? COL_DEF_TEXT : COL_UNKNOWN_FEATURE;

      if (!f_entity_valid) ev= CHR_UNKNOWN_FEATURE;
      *repl_array= (char) ev;
      *repl_size= 1;
      ft->ftr_display_mode= FTR_display_replarray;
      ft->ftr_replarray_size= 1;
      return (f_entity_valid) ? 1 : 0;

    case Ftype_SGML_TAG:
      /* Built in tag display options: hyx.l */
      if ((strncmp (lin, "hyx.l ", 6) == 0
           || strncmp (lin, "HLINK ", 6) == 0
          )
          && wc != (struct WINDOWCTRL *) 0              /* Logic Link Info  */
         )                                              /* kommt ins WINDOW */
      {
        ev= wc->wc_ll_flags;
        if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "dir") != -1)
        {
          if (strcmp (attr_value, "next") == 0) ev |= LL_next; else
          if (strcmp (attr_value, "prev") == 0) ev |= LL_prev; else
          if (strcmp (attr_value, "up"  ) == 0) ev |= LL_up;   else
          if (strcmp (attr_value, "lang") == 0) ev |= LL_lang; else
          if (strcmp (attr_value, "sort") == 0) ev |= LL_sort; else
          if (strcmp (attr_value, "view") == 0) ev |= LL_view; else

#ifdef LL_BUTTONS_1
          if (strcmp (attr_value, "menu") == 0)
          { /* only when there are no other logic links */
            if (!(ev & LL_more)) ev |= LL_menu;
          }
          else
          { /* other logic links override menu link */
            ev |= LL_more;
            ev &= ~LL_menu;
          }
#endif

#ifdef LL_BUTTONS_2
          if (strcmp (attr_value, "menu") == 0) ev |= LL_menu; else
          ev |= LL_more;
#endif
        }
        else ev |= LL_;

        wc->wc_ll_flags= ev;
      }

#ifdef LATER /* testing out problems ... */
      if (strncmp (lin, "stamp ", 6) == 0) return 1; /* -> destroy tag */
#endif

      /* Built in tag display options: Frame */
      if (strncmp (lin, "Frame ", 6) == 0
          || strncmp (lin, "hyx.f ", 6) == 0
          || lin [0] == ':'
         )
      {
        f_builtin_dispopt=1;
        ft->ftr_colour= COL_FRAME_TAGS;
        ft->ftr_display_mode= FTR_display_replarray;
#ifndef V1
        strcpy (repl_array, "<Frame>");
        ft->ftr_replarray_size= *repl_size = 7;
#else
        if (strlen (lin) > repl_max-2) lin [strlen(lin)-3]= 0;
        sprintf (repl_array, "<%s>", lin);
        ft->ftr_replarray_size= *repl_size= strlen (repl_array);
#endif
        ft->ftr_duplication= STD_dont_delete; /* thus: STD_no_dup!! */
        ft->ftr_edit_flags= FTR_EDIT_PROTECTED;
      } /* <Frame> */

      /* Built in tag display options: /Frame */
      if (strncmp (lin, "/Frame", 6) == 0
          || strncmp (lin, "/hyx.f", 6) == 0
          || lin [0] == ';'
         )
      {
        f_builtin_dispopt= 1;
        ft->ftr_colour= COL_FRAME_TAGS;
#ifndef V1
        strcpy (repl_array, "</Frame>");
        ft->ftr_replarray_size= *repl_size= 8;
#else
        if (strlen (lin) > repl_max-2) lin [strlen(lin)-3]= 0;
        sprintf (repl_array, "<%s>", lin);
        ft->ftr_replarray_size= *repl_size= strlen (repl_array);
#endif
        ft->ftr_display_mode= FTR_display_replarray;
        ft->ftr_duplication= STD_dont_delete; /* thus: STD_no_dup!! */
        ft->ftr_edit_flags= FTR_EDIT_PROTECTED;
      } /* </Frame> */

      /* externally defined display options for a tag */
      tag_desc= find_sgml_tag_descriptor (lin);

      if (tag_desc != (struct SGML_TAG_DESCRIPTOR *) 0
          && f_builtin_dispopt
          && tag_desc->STD_tag_mm == 1
         )
        tag_desc= (struct SGML_TAG_DESCRIPTOR *) 0;

      if (tag_desc == (struct SGML_TAG_DESCRIPTOR *) 0
          && !f_builtin_dispopt
         ) tag_desc= &_STD_NULL;

      if (tag_desc != (struct SGML_TAG_DESCRIPTOR *) 0)
      {
        ft->ftr_subtype=        tag_desc->STD_tag_id;
        ft->ftr_display_mode=   tag_desc->STD_display_mode;
        ft->ftr_colour=         tag_desc->STD_display_colour;
        ft->ftr_replarray_size=
          *repl_size=           tag_desc->STD_replarray_size;

        strcpy_max (repl_array,
                    (tag_desc->STD_replarray == (char *) 0)
                    ? "<?>" : tag_desc->STD_replarray,
                    repl_max);

        ft->ftr_weight=         tag_desc->STD_weight;
        ft->ftr_duplication=    tag_desc->STD_duplication;
      }

      /* override tag display mode, if configured this way */
      switch (wc->wc_tag_display_mode)
      { /* T2D: coordinate names of constants */
        case WCTDM_show_tag:
          ft->ftr_display_mode= STD_display_tag_name;
          break;
        case WCTDM_show_full_tag:
          ft->ftr_display_mode= STD_display_tag;
          break;
      }

      if (ft->ftr_display_mode == STD_display_tag
          || ft->ftr_display_mode == STD_display_tag_name
         )
      {
        copy_tag (repl_array, lin, repl_max, ft->ftr_display_mode);
        ft->ftr_display_mode= STD_display_replarray;
        ft->ftr_replarray_size= *repl_size= strlen (repl_array);
      }

      /* explicitly declared display options */
      if (wc->wc_tag_display_mode == WCTDM_normal)
      {
        if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "td") != -1)
        {
          if (strcmp (attr_value, "h") == 0)
          {
            ft->ftr_display_mode= FTR_display_hide;
          } else
          if (strcmp (attr_value, "p") == 0)
          {
            ft->ftr_display_mode= FTR_display_point;
          } else
          if (strcmp (attr_value, "r") == 0)
          {
            ft->ftr_display_mode= FTR_display_region;
            ft->ftr_replarray_size= 1;
          }
          *repl_size= 0;
        }

        if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "tdp") != -1)
        {
          ft->ftr_replarray_size= (int) get_parameter_value (attr_value);
          ft->ftr_display_mode= FTR_display_point;
          *repl_size= 0;
        }
      }

      if (find_attr_value (lin, repl_array, repl_max, "tds") != -1)
      {
        *repl_size= ft->ftr_replarray_size= strlen (repl_array);
        ft->ftr_display_mode= FTR_display_replarray;
      }

      if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "tdc") != -1)
      {
        ft->ftr_colour= identify_colour_code (attr_value);
      }

      if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "bgcol") != -1)
      {
        wc->attr_text= identify_colour_code (attr_value);
      }

      if (find_attr_value (lin, attr_value, ATTR_VALUE_SIZE, "marker") != -1)
      {
        struct MARKER *m;

        if (lp != (struct LINE *) 0
            && (m= ned_get_marker (*attr_value & 0x00FF, 1))
                   != (struct MARKER *) 0
           )
          ned_set_marker2 (wc, lp, offset, m);
      }

      return 0;

    default:
      return 0;
  }
}
