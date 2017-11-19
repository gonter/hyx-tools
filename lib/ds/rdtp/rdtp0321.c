/*
 *  FILE %ds/rdtp/rdtp0321.c
 *
 *  restructured dynamic text parser
 *  process a declaration
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-15 21:26:33
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
int sgml_declaration_done (struct RDTP_THREAD *thr, int ch)
{
  struct SGML_BUILDUP *sb;
  struct SGML_TOKEN *token;
  struct ARRAY_CONTROL *token_list;
  char *declaration_type;

#ifdef MSDOS
  ch;
#endif

  if (thr == (struct RDTP_THREAD *) 0
      || (sb= (struct SGML_BUILDUP *) thr->payload)
          == (struct SGML_BUILDUP *) 0
     )
  {
    rdtp_bad_thread ("rdtp0321");
    return -1;
  }

  if ((token_list= sb->tokens) == (struct ARRAY_CONTROL *) 0)
  {
    printf ("Warning: empty token list!\n");
    return 0;
  }

  token= (struct SGML_TOKEN *) array_shift (token_list);
  if (token->type != SGML_tokt_literal
      || (declaration_type= token->contents) == (char *) 0
     )
  {
    printf ("warning: unknown declaration format!\n");
    goto DONE;
  }

  to_lower (declaration_type);
  printf ("declaration type: '%s'\n", declaration_type);

  if (strcmp (declaration_type, "element") == 0)
  {
    sgml_element_declaration (sb, token_list, 0);
    /* NOTE: token_list is currently reused */
    goto COMPLETELY_DONE;
  }
  else
  if (strcmp (declaration_type, "attlist") == 0)
  {
    struct SGML_TOKEN *tok2;

    if ((tok2= (struct SGML_TOKEN *) array_shift (token_list))
           == (struct SGML_TOKEN *) 0)
      return -1;

    if (tok2->type == SGML_tokt_literal
        && strcmp_c (tok2->contents, "#notation") == 0
       )
    { /* Notation attribute */
      /* T2D */
    }
    else
    {
      array_unshift (token_list, tok2);
      sgml_element_declaration (sb, token_list, 1);
    }
  }
  
DONE:
  token_list->element_destructor= sgml_destroy_token;
  array_dispose (token_list);

COMPLETELY_DONE:
  sb->tokens= (struct ARRAY_CONTROL *) 0;

  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_declaration_done2 (struct RDTP_THREAD *thr, int ch)
{
  sgml_decl_token_end (thr, ch);
  return sgml_declaration_done (thr, ch);
}
