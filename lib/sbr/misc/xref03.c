/*
 *  FILE %sbr/xref02.c
 *
 *  Cross Reference Generator
 *  - resolver
 *
 *  written:       1997-08-03
 *  latest update: 1997-08-15 21:38:03
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/filename.h>
#include <gg/xref.h>

/* ------------------------------------------------------------------------ */
int xref_do_resolve (
struct XREF_RESOLVE *res,
int show_resolved,
int show_unresolved)
{
  struct ARRAY_CONTROL *ac;
  struct XREF_PUBLIC *pub;
  struct XREF_MODULE *mod;      /* currently processed module               */
  struct XREF_MODULE *modi;     /* imported module                          */
  struct XREF_CONTEXT *ctx;
#define MAX_BUFFER 120
  char buffer [MAX_BUFFER];
  char *name;

  char *mod_name;               /* name of module as recorded in obj file   */
  char *obj_name;               /* name of object file as recorded in lib   */
  char *dir_name;               /* name of directory for source file        */

  if (res == (struct XREF_RESOLVE *) 0
      || (ctx= res->ctx) == (struct XREF_CONTEXT *) 0
     )
  {
    printf ("NULL resolver, nothing to do!\n");
    return -1;
  }

  if ((ac= res->unresolved) == (struct ARRAY_CONTROL *) 0)
  {
    printf ("nothing to resolve!\n");
    return 0;
  }

  while ((name= (char *) array_shift (ac)) != (char *) 0)
  {
    if (ytree_get_value (res->ignore, (UCHAR *) name) != 0L)
    {
      goto NEXT;        /* resolver should ignore this item */
    }

    if (ytree_get_value (res->resolved, (UCHAR *) name) > 0L)
    {
      ytree_increment_value (&res->resolved, (UCHAR *) name, 1L);
      goto NEXT;        /* already resolved */
    }

    if ((pub= (struct XREF_PUBLIC *)
              ytree_get_value (ctx->publics, (UCHAR *) name))
          == (struct XREF_PUBLIC *) 0
        || (mod= pub->module) == (struct XREF_MODULE *) 0
       )
    { /* symbol could not be found anywhere */
      ytree_increment_value (&res->not_found, (UCHAR *) name, 1L);
      goto NEXT;
    }

    mod_name= mod->name;
    ytree_increment_value (&res->resolved, (UCHAR *) name, 1L);

    if ((modi= (struct XREF_MODULE *)
               ytree_get_value (res->imported, (UCHAR *) mod_name))
               != (struct XREF_MODULE *) 0
       )
    {
      printf ("%s imported with %s\n", name, mod_name);
      goto NEXT;
    }

    /* print require statement */
    printf ("%s requires %s\n", name, mod_name);
    if ((obj_name= mod->object_name) != (char *) 0)
      printf ("object: %s.obj\n", obj_name);
    if ((dir_name= get_module_directory (mod_name)) != (char *) 0)
      printf ("source: %s/%s\n", dir_name, mod_name);

    ytree_set_value (&res->imported, (UCHAR *) mod_name, (long) mod);

    if (mod->externals != (struct YTREE *) 0)
    {
      printf ("BEGIN import list for %s\n", mod_name);

      ytree_track (mod->externals, buffer, MAX_BUFFER, 0,
                   xref_resolve_symbols, (void *) res);

      printf ("END of import list for %s\n", mod_name);
    }

NEXT:
    free (name);
  }

  if (show_unresolved && res->not_found != (struct YTREE *) 0)
  {
    printf ("BEGIN list of unresolved symbols (number of refs, name)\n");
    ytree_track_info (res->not_found, buffer, MAX_BUFFER, 0,
                      xref_print_ref_list, (void *) "  ");
    printf ("END list of unresolved symbols\n");
  }

  if (show_resolved && res->resolved != (struct YTREE *) 0)
  {
    printf ("BEGIN list of resolved symbols (number of refs, name)\n");
    ytree_track_info (res->resolved, buffer, MAX_BUFFER, 0,
                      xref_print_ref_list, (void *) "  ");
    printf ("END list of resolved symbols\n");
  }

  return 0;
}
