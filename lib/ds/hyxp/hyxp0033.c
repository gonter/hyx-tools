/*
 *  FILE %ds/hyxp/hyxp0033.c
 *
 *  Verwaltung von TAG Defintionen
 *
 *  written:       1991 03 12
 *  latest update: 2001-02-18 18:44:54
 *  $Id: hyxp0033.c,v 1.5 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/ytree.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
struct TAG_DEFINITION *hyx_make_tag_definition (
struct HYX_PARSER_CLASS *hpc,
char *str,
long id,
int mm,
long weight,
int ty,
char *comment)
{
  struct TAG_DEFINITION *t;

  if ((t= hyx_new_tag_definition ()) == (struct TAG_DEFINITION *) 0)
     return (struct TAG_DEFINITION *) 0;

  hpc->HPC_TAG_DEFINITION_allocated++;

  if (hpc->HPC_meta_flags & HPC_META_show_new_tags)
  {
    printf ("[0x%08lX] new tag str='%s' id=%ld mm=%d\n", t, str, id, mm);
  }

  t->sig= SIG_TAG_DEFINITION;
  t->TAG_DEF_next= (struct TAG_DEFINITION *) 0;
  t->match_mode= mm;
  t->tag_id= id;
  t->tag_type= ty;
  t->tag_weight= weight;
  t->tag_name= strdup (str);
  if (comment != (char *) 0) t->tag_comment= strdup (comment);

  *(hpc->HPC_tag_append)= t;
  hpc->HPC_tag_append= &t->TAG_DEF_next;

  ytree_set_value (&hpc->HPC_tags, t->tag_name, (long) t);

  return t;
}
