/*
 *  FILE %ds/rdtp/rdtp0318.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-09-15
 *  latest update: 1999-04-25 16:57:59
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct SGML_TOKEN *sgml_tokenizer (char *str, int type)
{
  struct SGML_TOKEN *token;

  if ((token= (struct SGML_TOKEN *) calloc (sizeof (struct SGML_TOKEN), 1))
      != (struct SGML_TOKEN *) 0
     )
  {
    /****** printf ("tokenize: '%s' ty=%d\n", str, type); *****/
    token->contents= strdup (str);
    token->type= type;
  }

  return token;
}

/* ------------------------------------------------------------------------ */
void sgml_destroy_token (void *pl)
{
  struct SGML_TOKEN *token;
  char *str;

  if ((token= (struct SGML_TOKEN *) pl) != (struct SGML_TOKEN *) 0)
  {
    if ((str= token->contents) != (char *) 0)
    {
      printf ("destroy token: %2d '%s'\n", token->type, str);
      free (str);
    }
    free (token);
  }
}

/* ------------------------------------------------------------------------ */
void sgml_free_token (struct SGML_TOKEN *token)
{
  char *str;

  if (token != (struct SGML_TOKEN *) 0)
  {
    if ((str= token->contents) != (char *) 0) free (str);
    free (token);
  }
}
