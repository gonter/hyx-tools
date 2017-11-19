/*
 *  FILE %ned/08/ned0831.c
 *
 *  written:       1991 01 30
 *  latest update: 1999-04-25 16:32:53
 *  $Id: ned0831.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include <gg/sbr.h>
#include "ed.h"
#include "edhyx.h"
#include <gg/window.h>
#include "proto.h"

#ifndef MAX_TAG_NAME
#define MAX_TAG_NAME 48
#endif

static int cdecl dummy (char *str, int opt);
static int dummy (char *str, int opt) { opt= *str; return 0; }

/* ------------------------------------------------------------------------ */
#define LAST_ONE _STD_NED_PARAMETER
static struct SGML_TAG_DESCRIPTOR _STD_NED_PARAMETER =
{
  (struct SGML_TAG_DESCRIPTOR *) 0,
  "ned.par",
  7,
  0,
  STID_NED_PARAMETER,
  eval_ned_parameter,
  dummy,
  STD_display_hide,
  WV_GELB,
  STD_no_dup,                   /* STD_duplication */
  0,                            /* STD_subtype          */
  100,
  0,
  (char *) 0
#ifdef DEVEL1
  ,
  0,0,0,0
#endif
} ;

/* ------------------------------------------------------------------------ */
#ifdef VW5
static struct SGML_TAG_DESCRIPTOR _STD_SOPH_Ans =
{
  &_STD_NED_PARAMETER,
  "Ans",
  3,
  0,
  1999,                         /* ID code */
  dummy,
  dummy,
  STD_display_hide,
  WV_GELB,
  STD_dup_copy,
  0,                            /* STD_subtype          */
  100,
  0,
  (char *) 0
#ifdef DEVEL1
  ,
  0,0,0,0
#endif
} ;

#endif

/* ------------------------------------------------------------------------ */
static struct SGML_TAG_DESCRIPTOR _STD_NED_MACRO =
{
#ifdef VW5
  &_STD_SOPH_Ans,
#else
  &_STD_NED_PARAMETER,
#endif
  "ned.mac",
  7,
  0,
  STID_NED_MACRO,
  eval_ned_macro,
  dummy,
  STD_display_hide,
  WV_GELB,
  STD_dup_copy,
  0,                            /* STD_subtype          */
  100,
  0,
  (char *) 0
#ifdef DEVEL1
  ,
  0,0,0,0
#endif
} ;

/* ------------------------------------------------------------------------ */
static struct SGML_TAG_DESCRIPTOR _STD_HLINK =
{
  &_STD_NED_MACRO,              /* STD_next             */
  "HLINK",                      /* STD_tag_name         */
  5,                            /* STD_tag_ml           */
  0,                            /* STD_tag_mm           */
  STID_hyx_l,                   /* STD_tag_id           */
  ned_eval_hlink,               /* STD_activated        */
  dummy,                        /* STD_scanned          */
  STD_display_point,            /* STD_display_mode     */
  WV_WEISS|W_HELL,              /* STD_display_colour   */
  STD_dup_copy|STD_dup_write,   /* STD_duplication      */
  0,                            /* STD_subtype          */
  100,                          /* STD_weight           */
#ifdef V1
  1,                            /* STD_replarray_size   */
  "*",                          /* STD_replarray        */
#else
  0,                            /* STD_replarray_size   */
  (char *) 0                    /* STD_replarray        */
#endif
#ifdef DEVEL1
  ,
  0,
  0,
  0,
  0                             /* STD_new#             */
#endif
} ;

/* ------------------------------------------------------------------------ */
static struct SGML_TAG_DESCRIPTOR _STD_hyx_l =
{
  &_STD_HLINK,                  /* STD_next             */
  "hyx.l",                      /* STD_tag_name         */
  5,                            /* STD_tag_ml           */
  0,                            /* STD_tag_mm           */
  STID_hyx_l,                   /* STD_tag_id           */
  ned_eval_hlink,               /* STD_activated        */
  dummy,                        /* STD_scanned          */
  STD_display_point,            /* STD_display_mode     */
  WV_WEISS|W_HELL,              /* STD_display_colour   */
  STD_dup_copy|STD_dup_write,   /* STD_duplication      */
  0,                            /* STD_subtype          */
  100,                          /* STD_weight           */
#ifdef V1
  1,                            /* STD_replarray_size   */
  "*"                           /* STD_replarray        */
#else
  0,                            /* STD_replarray_size   */
  (char *) 0                    /* STD_replarray        */
#endif
#ifdef DEVEL1
  ,
  0,
  0,
  0,
  0                             /* STD_new#             */
#endif
} ;

/* ------------------------------------------------------------------------ */
static struct SGML_TAG_DESCRIPTOR _STD_a =      /* HTML anchor */
{
  &_STD_hyx_l,                  /* STD_next             */
  "a",                          /* STD_tag_name         */
  1,                            /* STD_tag_ml           */
  0,                            /* STD_tag_mm           */
  STID_hyx_l,                   /* STD_tag_id           */
  ned_eval_hlink,               /* STD_activated        */
  dummy,                        /* STD_scanned          */
  STD_display_point,            /* STD_display_mode     */
  WV_WEISS|W_HELL,              /* STD_display_colour   */
  STD_dup_copy|STD_dup_write,   /* STD_duplication      */
  0x0001,                       /* STD_flags (formerly STD_subtype) */
  100,                          /* STD_weight           */
#ifdef V1
  1,                            /* STD_replarray_size   */
  "*"                           /* STD_replarray        */
#else
  0,                            /* STD_replarray_size   */
  (char *) 0                    /* STD_replarray        */
#endif
#ifdef DEVEL1
  ,
  0,
  0,
  0,
  0                             /* STD_new#             */
#endif
} ;

/* ------------------------------------------------------------------------ */
struct SGML_TAG_DESCRIPTOR _STD_PSEUDO =
{
  &_STD_a,
  (char *) 0,
  0,
  0,
  STID_PSEUDO,
  dummy,
  dummy,
  STD_display_replarray,/* Pseudo Character fÅr Tag einsetzen               */
                        /* normalerweise ist das das evaluierte Zeichen     */
  WV_GELB,              /* ### */
  STD_no_dup,                    /* ### */
  0,                            /* STD_subtype          */
  100,
  1,
  "\x03"
#ifdef DEVEL1
  ,
  0,0,0,0
#endif
} ;

/* ------------------------------------------------------------------------ */
struct SGML_TAG_DESCRIPTOR _STD_NULL =
{
  &_STD_PSEUDO,
  (char *) 0,
  0,
  0,
  STID_NULL,
  dummy,
  dummy,
  STD_display_point,
  WV_GELB|W_HELL,
  STD_dup_always,
  0,                            /* STD_subtype          */
  100,
  0,
  (char *) 0
#ifdef DEVEL1
  ,
  0,0,0,0
#endif
} ;

/* ------------------------------------------------------------------------ */
static struct SGML_TAG_DESCRIPTOR
   *tag_table  = &_STD_NULL,
  **tag_append = &((LAST_ONE).STD_next);

/* ------------------------------------------------------------------------ */
int setup_sgml_tag_descriptors (const char *setup_file_name)
{
  FILE *fi;
  struct SGML_TAG_DESCRIPTOR *st;

  char *tag_name;
  char *repl_array;
  int tag_id;
  int tag_mm;
  int display_mode;
  int display_colour;
  int duplication;

  int rc;
  int sc;
#define MAX_BUFFER 128
#define MAX_FIELDS 10
  char *buffer= (char *) 0;
  char *fields [MAX_FIELDS];

  if (setup_file_name == (char *) 0
      || *setup_file_name == 0
      || (fi= fopen (setup_file_name, "rb")) == (FILE *) 0
      || (buffer= malloc (MAX_BUFFER)) == (char *) 0
     ) return -1;

  for (;;)
  {
    rc= fread_line (fi, buffer, MAX_BUFFER);
    if (rc <= 0 && feof (fi)) break;
    if (buffer [0] == '#') continue;

    sc= isolate_tokens (buffer, fields, MAX_FIELDS);
    if (sc < 6) continue;

    tag_name= fields [0];
    tag_id= (int) get_parameter_value (fields [1]);
    tag_mm= (int) get_parameter_value (fields [2]);
    display_mode= (int) get_parameter_value (fields [3]);
    display_colour= (int) get_parameter_value (fields [4]);
    duplication= (int) get_parameter_value (fields [5]);
    repl_array= (sc >= 6) ? fields [6] : (char *) 0;

    st= find_sgml_tag_descriptor (tag_name);
    if (st == (void *) 0)
    {
      if ((st= (struct SGML_TAG_DESCRIPTOR *)
               calloc (sizeof (struct SGML_TAG_DESCRIPTOR), 1))
         == (struct SGML_TAG_DESCRIPTOR *) 0) break;

      if (strcmp (tag_name, "*") == 0)
      {
        st->STD_tag_name= "";
        st->STD_tag_ml= 0;
        st->STD_tag_mm= 1;
      }
      else
      {
        st->STD_tag_name= strdup (tag_name);
        st->STD_tag_ml=   strlen (tag_name);
        st->STD_tag_mm=   tag_mm;
      }
      /* st->STD_next= (struct SGML_TAG_DESCRIPTOR *) 0; ... calloc'ed */
      *tag_append= st;
       tag_append= &st->STD_next;
    }

    st->STD_tag_id=         tag_id;
    st->STD_display_mode=   display_mode;
    st->STD_display_colour= display_colour;
    st->STD_duplication=    duplication;

    /* st->STD_replarray_size= 0; ... calloc'ed */
    /* st->STD_replarray= (char *) 0;    ... calloc'ed */

    if (repl_array != (char *) 0)
    {
      st->STD_replarray_size= strlen (repl_array);
      st->STD_replarray= strdup (repl_array);
    }
  }

  fclose (fi);
  free_or_what (buffer);

  return 0;
}

/* ------------------------------------------------------------------------ */
void reset_sgml_tag_descriptors ()
{
  struct SGML_TAG_DESCRIPTOR *st1, *st2;

  for (st1= (LAST_ONE).STD_next;
       (st2= st1) != (struct SGML_TAG_DESCRIPTOR *) 0;)
  {
    st1= st1->STD_next;
    free_or_what (st2->STD_tag_name);
    free_or_what (st2->STD_replarray);
    free (st2);
  }

  tag_table= &_STD_NULL;
  tag_append= &((LAST_ONE).STD_next);
}

/* ------------------------------------------------------------------------ */
struct SGML_TAG_DESCRIPTOR *get_sgml_tag_descriptor (int tag_id)
{
  struct SGML_TAG_DESCRIPTOR *st;

  for (st= tag_table;
       st != (struct SGML_TAG_DESCRIPTOR *) 0;
       st= st->STD_next)
    if (st->STD_tag_id == tag_id) return st;

  return (struct SGML_TAG_DESCRIPTOR *) 0;
}

/* ------------------------------------------------------------------------ */
struct SGML_TAG_DESCRIPTOR *find_sgml_tag_descriptor (char *tag)
{
  struct SGML_TAG_DESCRIPTOR *st;
  int ml, cml;

  if (tag == (char *) 0) return (struct SGML_TAG_DESCRIPTOR *) 0;

  for (st= tag_table;
       st != (struct SGML_TAG_DESCRIPTOR *) 0;
       st= st->STD_next)
  {
    if (st->STD_tag_name == (char *) 0) continue;
    ml= st->STD_tag_ml;
    cml= tag[ml];

    if (strncmp (st->STD_tag_name, tag, ml) == 0
       && (st->STD_tag_mm == 1
          || cml==0x20 || cml==0 || cml==0x09 || cml==0x0A || cml==0x0D))
      return st;
  }

  return (struct SGML_TAG_DESCRIPTOR *) 0;
}
