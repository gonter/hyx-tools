/*
 *  FILE %ds/rdtp/rdtp0421.c
 *
 *  restructured dynamic text parser
 *  return an array representing a name group or a single name
 *
 *  see {GF [69] 374:11} for details
 *
 *  Options: group required indicates that a single name is invalid
 *
 *  written:       1996-09-15
 *  latest update: 1999-04-25 16:58:05
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct ARRAY_CONTROL *sgml_get_name_or_group (
struct ARRAY_CONTROL *token_list,
int group_required)             /* 1 -> (name) required */
{
  struct ARRAY_CONTROL *element_names= (struct ARRAY_CONTROL *) 0;
  struct SGML_TOKEN *tok;
  char *str_element_name;
  int tokt;
  char *reason;

  element_names= array_new ();
  /* get list of enlement names */
  if ((tok= (struct SGML_TOKEN *) array_shift (token_list))
         == (struct SGML_TOKEN *) 0
     )
  {
    reason= "no tokens";

INVALID:
    printf ("error: (rdtp0403) invalid name group: '%s'\n", reason);

    element_names->element_destructor= free;
    array_dispose (element_names);
    return (struct ARRAY_CONTROL *) 0;
  }

  if (tok->type == SGML_tokt_begin_group)
  {
    sgml_free_token (tok);

    for (;;)
    {
      if ((tok= (struct SGML_TOKEN *) array_shift (token_list))
             == (struct SGML_TOKEN *) 0
          || tok->type != SGML_tokt_literal
         )
      {
        reason= "no gr literal";
        goto INVALID;
      }

      str_element_name= tok->contents;
      to_lower (str_element_name);
      array_push (element_names, (void *) str_element_name);
      free (tok);

      if ((tok= (struct SGML_TOKEN *) array_shift (token_list))
             == (struct SGML_TOKEN *) 0)
      {
        reason= "no gr follower";
        goto INVALID;
      }

      tokt= tok->type;
      sgml_free_token (tok);

      if (tokt == SGML_tokt_end_group) break;

      if (tokt != SGML_tokt_comma
          && tokt != SGML_tokt_or
          && tokt != SGML_tokt_and
         )
      {
        reason= "no gr connector";
        goto INVALID;
      }
    }
  }
  else
  if (tok->type == SGML_tokt_literal && !group_required)
  {
    str_element_name= tok->contents;
    to_lower (str_element_name);
    array_push (element_names, (void *) str_element_name);
    free (tok);
  }
  else
  {
    reason= "inv. token";
    sgml_free_token (tok);
    goto INVALID;
  }

  return element_names;
}
