/*
 *  FILE %ds/rdtp/rdtp0322.c
 *
 *  restructured dynamic text parser
 *  add a tag name to a document instance
 *
 *  written:       1997-06-16
 *  latest update: 1997-06-16 13:57:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct SGML_TAG_NAME *sgml_add_element (
struct SGML_BUILDUP *sb,
char *element)
{
  struct SGML_TAG_NAME *element_name;
  struct YTREE *yt;

  if ((yt= ytree_insert_word (&sb->element_names, (unsigned char *) element))
             == (struct YTREE *) 0)
  {
IE:
    fprintf (stderr, "rdtp0309: internal error\n");
    return (struct SGML_TAG_NAME *) 0;
  }

  if (!(yt->YT_flags & YTflag_EOW))
  {
    element_name= sgml_new_element_name (sb, element);

    yt->YT_flags |= YTflag_EOW;
    yt->YT_info= (long) element_name;
  }
  else
  {
    element_name= (struct SGML_TAG_NAME *) yt->YT_info;
  }

  if (element_name == (struct SGML_TAG_NAME *) 0) goto IE;

  element_name->ref_counter++;

  return element_name;
}
