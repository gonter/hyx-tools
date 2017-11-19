/*
 *  FILE %ds/rdtp/rdtp0313.c
 *
 *  restructured dynamic text parser: SGML
 *
 *  written:       1996-06-23
 *  latest update: 1997-06-16 20:01:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct SGML_TAG_NAME *sgml_new_element_name (
struct SGML_BUILDUP *ctx,
char *name)
{
  struct SGML_TAG_NAME *element= (struct SGML_TAG_NAME *) 0;
  struct YTREE *yt;

  /***** printf ("new element name: '%s'\n", name); ******/

  if ((element= calloc (sizeof (struct SGML_TAG_NAME), 1))
            != (struct SGML_TAG_NAME *) 0
      && (element->tag_name= strdup (name)) != (char *) 0
     )
  {
    if ((yt= ytree_lookup_word (ctx->defined_element_names, name))
             != (struct YTREE *) 0
        && (yt->YT_flags & YTflag_EOW)
       )
     element->tag_def= (struct SGML_ELEMENT_DECLARATION *) yt->YT_info;
  }

  return element;
}
