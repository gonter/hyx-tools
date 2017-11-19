/*
 *  FILE %ned/08/ned0830.c
 *
 *  ###### TO BE REVISED !!!!! #####
 *  *** NOT USED ***
 *
 *  written:       1991 07 01
 *  latest update: 1999-04-25 16:32:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ed.h"
#include "edhyx.h"
#include <gg/window.h>
#include "proto.h"

#ifndef MAX_ENTITY_NAME
#define MAX_ENTITY_NAME 48
#endif

/* ------------------------------------------------------------------------ */
static struct SGML_ENTITY_DESCRIPTOR  *entity_table=
  (struct SGML_ENTITY_DESCRIPTOR *) 0;
static struct SGML_ENTITY_DESCRIPTOR **entity_append= &entity_table;

/* ------------------------------------------------------------------------ */
int setup_sgml_entity_descriptors (char *setup_file_name)
{
#ifdef MSDOS
  setup_file_name;
#endif

#ifdef JUNK
  FILE *fi;
  struct SGML_ENTITY_DESCRIPTOR *st;

  char  tag_name [MAX_TAG_NAME];
  int   tag_id;
  int   display_mode;
  int   display_colour;
  int   display_character;
  int   duplication;

  if (setup_file_name == (char *) 0 || *setup_file_name == 0) return -1;
  fi = fopen (setup_file_name, FILE_TEXT_READ);
  if (fi == (FILE *) 0) return -1;

  for (;;)
  {
    fscanf (fi, "%s", tag_name);
    if (feof (fi)) break;
    if (tag_name [0] == '#')
    {
      while (!feof(fi) && fgetc(fi)!='\n');
      continue;
    }
    fscanf (fi, "%x%x%x%x%x",
            &tag_id,
            &display_mode,
            &display_colour,
            &display_character,
            &duplication);
    if (feof (fi)) break;

    st = calloc (sizeof (struct SGML_ENTITY_DESCRIPTOR), 1);
    if (st == (void *) 0) break;
    st->STD_tag_name       = strdup (tag_name);
    st->STD_tag_id         = tag_id;
    st->STD_display_mode   = display_mode;
    st->STD_display_colour = display_colour;
/** st->STD_display_character=display_character; ############## */
    st->STD_duplication    = duplication;
    st->STD_next           = (struct SGML_TAG_DESCRIPTOR *) 0;

    *entity_append = st;
     entity_append = &st->STD_next;
  }
  fclose (fi);
#endif

  return 0;
}

/* ------------------------------------------------------------------------ */
void reset_sgml_entity_descriptors ()
{
#ifdef JUNK
  struct SGML_ENTITY_DESCRIPTOR *st1, *st2;

  for (st1 = entity_table; (st2=st1) != (void *) 0;)
  {
    st1 = st1->STD_next;
    free (st2);
  }
#endif

  entity_table= (struct SGML_ENTITY_DESCRIPTOR *) 0;
  entity_append= &entity_table;
}

/* ------------------------------------------------------------------------ */
struct SGML_ENTITY_DESCRIPTOR *get_sgml_entity_descriptor (int tag_id)
{
#ifdef MSDOS
  tag_id;
#endif

#ifdef JUNK
  struct SGML_ENTITY_DESCRIPTOR *st;

  for (st  = entity_table;
       st != (void *) 0;
       st  = st->STD_next)
    if (st->STD_tag_id == tag_id) return st;
#endif

  return (void *) 0;
}

/* ------------------------------------------------------------------------ */
struct SGML_ENTITY_DESCRIPTOR *find_sgml_entity_descriptor (char *tag)
{
#ifdef MSDOS
  tag;
#endif

#ifdef JUNK
  struct SGML_ENTITY_DESCRIPTOR *st;
  int ml, cml;

  for (st  = entity_table;
       st != (void *) 0;
       st  = st->STD_next)
  {
    if (st->STD_tag_name == (char *) 0) continue;
    ml = st->STD_tag_ml;
    cml = tag[ml];
    if (strncmp (st->STD_tag_name, tag, ml) == 0
       && (st->STD_tag_mm == 1
          || cml==0x20 || cml==0 || cml==0x09 || cml==0x0A || cml==0x0D))
      return st;
  }
#endif

  return (void *) 0;
}
