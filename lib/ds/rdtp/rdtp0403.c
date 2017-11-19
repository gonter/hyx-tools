/*
 *  FILE %ds/rdtp/rdtp0403.c
 *
 *  restructured dynamic text parser
 *  process a element or attlist declaration
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-22 13:00:12
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/dpp.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_can_be_minimized (char *str)
{
  if (str == (char *) 0) return -1;
  if (strcmp (str, "O") == 0) return 1;
  if (strcmp (str, "-") == 0) return 0;
  return -1;
}

/* ------------------------------------------------------------------------ */
int sgml_can_be_minimized_tok (struct SGML_TOKEN *tok)
{
  if (tok == (struct SGML_TOKEN *) 0
      || (tok->type != SGML_tokt_literal
          && tok->type != SGML_tokt_dash
         )
     )
    return -1;

  return sgml_can_be_minimized (tok->contents);
}

/* ------------------------------------------------------------------------ */
int sgml_element_declaration (
struct SGML_BUILDUP *sb,
struct ARRAY_CONTROL *token_list,
int what)                               /* 0 -> element declaration         */
                                        /* 1 -> attlist declaration         */
{
  struct SGML_TOKEN *tok;
  char *element_name;
  int minim_beg;
  int minim_end;
  long rank= 0L;
  int repeater;
  struct YTREE *yt;
  struct SGML_ELEMENT_DECLARATION *ed;
  struct SGML_ATTLIST_DECL *attlist;
  struct SGML_CONTENT_MODEL *cont_mod;
  struct ARRAY_CONTROL *element_names;

  /* {GF [117] 406:1} */
  if ((element_names= sgml_get_name_or_group (token_list, 0))
        == (struct ARRAY_CONTROL *) 0)
  {
    printf ("error: invalid element name (or list)\n");
    return -1;
  }

  if (what == 0)
  { /* element declaration */

    /* look at the next token for a rank or minimization */
    for (repeater= 2; repeater > 0; repeater--)
    {
      if ((tok= (struct SGML_TOKEN *) array_shift (token_list))
            == (struct SGML_TOKEN *) 0)
      {
        printf ("error: invalid element declaration\n");
        return -1;
      }

      if (repeater == 1) break; /* only one rank code! */
      if (tok->type == SGML_tokt_number)
      { /* there's a rank code, whatever that is! */
        printf ("note: there's a ranking code!\n");
        rank= get_parameter_value (tok->contents);
      }
      else break;
    }

    /* check for minimization options */
    if ((minim_beg= sgml_can_be_minimized_tok (tok)) == -1)
    {
      minim_beg= minim_end= 0;
      array_unshift (token_list, tok);
    }
    else
    { /* token was a minimization token, there must be another one */
      sgml_free_token (tok);
  
      tok= (struct SGML_TOKEN *) array_shift (token_list);
      minim_end= sgml_can_be_minimized_tok (tok);
      sgml_free_token (tok);
    }

    /* T2D: process content model and produce a in-memory version */
    cont_mod= sgml_get_content_model (token_list);
  }

  if (what == 1 || what == 2)
  { /* attlist declaration */

    /* T2D: process attribute definition list */
    attlist= sgml_get_attlist (token_list);
  }

  /* register minimization options and content model for all element names */
  while ((element_name= (char *) array_shift (element_names))!= (char *) 0)
  {
    if ((yt= ytree_insert_word (&sb->defined_element_names, element_name))
               == (struct YTREE *) 0)
    {
OOM:
      printf ("error: (rdtp0403) out of memory!!\n");
      return -1;
    }

    if (yt->YT_flags & YTflag_EOW)
    {
      printf ("warning: (rdtp0403) redeclaration of element '%s'\n");
      ed= (struct SGML_ELEMENT_DECLARATION *) yt->YT_info;
      free (element_name);
    }
    else
    {
      yt->YT_flags |= YTflag_EOW;
      ed= sgml_new_element_declaration ();
      yt->YT_info= (long) ed;
      ed->name= element_name;
    }

    if (ed == (struct SGML_ELEMENT_DECLARATION *) 0) goto OOM;

    /* T2D: If there are other element names left, copy in-memory version   */
    /*      of the content model and use that here, otherwise use the       */
    /*      the processed model directly.                                   */
    /*      Alternatively, link to the content model and increment          */
    /*      a reference counter.                                            */

    if (what == 0)
    {
      ed->minim_start= minim_beg;
      ed->minim_end=   minim_end;
      ed->rank=        rank;

      ed->cont_mod=    cont_mod;
      cont_mod->ref_count++;
    }

    if (what == 1)
    {
      ed->attlist= attlist;
      attlist->ref_count++;
    }

    sgml_print_element_declaration (stdout, ed);
  }

  array_dispose (element_names);

  return 0;
}
