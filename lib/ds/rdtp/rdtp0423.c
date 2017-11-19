/*
 *  FILE %ds/rdtp/rdtp0423.c
 *
 *  restructured dynamic text parser
 *  process an attlist declaration
 *
 *  written:       1996-09-15
 *  latest update: 1999-04-25 16:58:13
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
#define NUM_DECL_VALUES 16
static char *DECLARED_VALUES [NUM_DECL_VALUES] =
{
  (char *) 0,
  "CDATA",
  "ENTITY",
  "ENTITIES",
  "ID",

  "IDREF",
  "IDREFS",
  "NAME",
  "NAMES",
  "NMTOKEN",

  "NMTOKENS",
  "NUMBER",
  "NUMBERS",
  "NUTOKEN",
  "NUTOKENS",

  "NOTATION"
} ;

/* ------------------------------------------------------------------------ */
int sgml_get_declared_value_code (char *str)
{
  int rc;

  to_upper (str);       /* T2D: this is only allowed if generic identifiers */
                        /* can be uppercased, that is, if the SGML          */
                        /* declaration states GENARAL NO in the NAME group! */

  rc= find_command (str, DECLARED_VALUES, 1, NUM_DECL_VALUES-1);
  if (rc < 0) rc= 0;
  return rc;
}

/* ------------------------------------------------------------------------ */
struct SGML_ATTLIST_DECL *sgml_get_attlist (
struct ARRAY_CONTROL *token_list)
{
  struct SGML_ATTLIST_DECL *attl;
  struct SGML_ATTRIBUTE_DECLARATION *attdecl, **attdecl_next;
  struct SGML_TOKEN *att_name, *att_defval;
  struct ARRAY_CONTROL *declared_value_list;
  char *declared_value;
  int declared_value_code;
  char *s1;

  if ((attl= sgml_new_attlist_decl ()) == (struct SGML_ATTLIST_DECL *) 0)
  {
NO_MEM:
    printf ("error: (rdtp0423) out of memory\n");
  }
  else
  {
    attdecl_next= &attl->attributes;

    for (;;)
    {
      /* {GF [141] 420:16} */
      /* attribute definition                                               */
      /*   = (<attribute name> <declared value> <default value>)+)          */

      /* {GF [144] 421:14} */
      if ((att_name= (struct SGML_TOKEN *) array_shift (token_list))
               == (struct SGML_TOKEN *) 0)
      { /* NOTE, T2D: this implementation allows empty attribute            */
        /*       declaration lists, this is not really correct!             */
        break;
      }

      if ((attdecl= sgml_new_attdecl ())
           == (struct SGML_ATTRIBUTE_DECLARATION *) 0
         )
        goto NO_MEM;

      if (att_name->type != SGML_tokt_literal
          || (s1= att_name->contents) == (char *) 0
         )
      {
ERROR:
        printf ("error: (rdtp0423) bad attribute list\n");
        break;
      }

      /* {GF [145] 422:6} */
      /* NOTE, T2D: notation attributes are not handleded! {GF [145] 423:11}*/
      if ((declared_value_list= sgml_get_name_or_group (token_list, 0))
          == (struct ARRAY_CONTROL *) 0) goto ERROR;

      attdecl->name= att_name->contents;
      free (att_name);

      if (array_elements (declared_value_list) == 1)
      {
        declared_value= (char *) array_shift (declared_value_list);
        declared_value_code= sgml_get_declared_value_code (declared_value);
printf (">> decval= '%s' = %d\n", declared_value, declared_value_code);

        array_dispose (declared_value_list);
        free (declared_value);
        /* NOTE, T2D: if this is a NOTATION, get another name or group */
      }
      else
      {
        declared_value_code= SGML_DECLVAL_name_tokg;
        attdecl->declared_value_ptr= declared_value_list;
      }
      attdecl->declared_value= declared_value_code;

      /* {GF [147] 425:1} */
      /* WORK: this is incomplete!!! */
      att_defval= (struct SGML_TOKEN *) array_shift (token_list);
      attdecl->default_value_ptr= att_defval->contents;

      *attdecl_next= attdecl;
      attdecl_next= &attdecl->next;
    }
  }

  return attl;
}
