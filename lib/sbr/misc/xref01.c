/*
 *  FILE %sbr/xref01.c
 *
 *  Cross Reference Generator
 *  - collect definitions
 *
 *  written:       1997-08-03
 *  latest update: 1997-09-14 17:15:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/xref.h>

/* ------------------------------------------------------------------------ */
struct XREF_MODULE *xref_module (
struct XREF_CONTEXT *ctx,
char *name,
int replace)
{
  struct XREF_MODULE *mod;
  struct XREF_MODULE *mod2= (struct XREF_MODULE *) 0;

  if (ctx == (struct XREF_CONTEXT *) 0
      || (mod= (struct XREF_MODULE *) calloc (sizeof (struct XREF_MODULE), 1))
           == (struct XREF_MODULE *) 0
     ) return (struct XREF_MODULE *) 0;

  /* populate module declaration with data */
  mod->name= strdup (name);
  mod->ctx= ctx;

  if ((mod2= (struct XREF_MODULE *)
             ytree_get_value (ctx->modules, (unsigned char *) name))
             != (struct XREF_MODULE *) 0
     )
  {
    if (replace)
    {
      mod->shadows= mod2;
      printf ("module %s replaces another instance\n", name);
    }
    else
    {
      struct XREF_MODULE **mp;
      int cnt= 2;

      /* find end of list of shadowed modules */
      for (mp= &mod2->shadows;
           *mp != (struct XREF_MODULE *) 0;
           mp= &(*mp)->shadows) cnt++;

      *mp= mod;

      printf ("module %s shadowed as instance %d\n", name, cnt);
      return mod;
    }
  }

  ytree_set_value (&ctx->modules, (UCHAR *) name, (long) mod);

  return mod;
}

/* ------------------------------------------------------------------------ */
int xref_set_object (
struct XREF_MODULE *mod,
char *name)
{
  if (mod == (struct XREF_MODULE *) 0
      || name == (char *) 0
     ) return -1;

  mod->object_name= strdup (name);

  return 0;
}

/* ------------------------------------------------------------------------ */
struct XREF_PUBLIC *xref_public (
struct XREF_MODULE *mod,
char *name)
{
  struct XREF_PUBLIC *pub;
  struct XREF_PUBLIC *pub2;
  struct XREF_CONTEXT *ctx;

  if (mod == (struct XREF_MODULE *) 0
      || (ctx= mod->ctx) == (struct XREF_CONTEXT *) 0
      || (pub= (struct XREF_PUBLIC *) calloc (sizeof (struct XREF_PUBLIC), 1))
               == (struct XREF_PUBLIC *) 0
     ) return (struct XREF_PUBLIC *) 0;

  if ((pub2= (struct XREF_PUBLIC *)
             ytree_get_value (ctx->publics, (UCHAR *) name))
             != (struct XREF_PUBLIC *) 0
     )
  { /* T2D: implement pub2 shadowing pub or vica versa */
    struct XREF_MODULE *mod2;

    mod2= pub2->module;

    printf ("%s already defined in %s (now in %s)\n",
            name, mod2->name, mod->name);
  }
  else
    ytree_set_value (&ctx->publics, (UCHAR *) name, (long) pub);

  ytree_set_value (&mod->publics, (UCHAR *) name, (long) pub);

#ifdef XREF_DEBUG1
  printf ("registering PUBLIC '%s' in '%s'\n", name, mod->name);
#endif /* XREF_DEBUG */

  pub->module= mod;
  pub->name= strdup (name);

  return pub;
}

/* ------------------------------------------------------------------------ */
int xref_external (
struct XREF_MODULE *mod,
char *name)
{
  if (mod == (struct XREF_MODULE *) 0) return -1;

  ytree_set_value (&mod->externals, (UCHAR *) name, (long) 0);

#ifdef XREF_DEBUG1
  printf ("registering EXTERNAL '%s' in '%s'\n", name, mod->name);
#endif /* XREF_DEBUG */

  return 0;
}
