/*
 *  include FILE <gg/xref.h>
 *
 *  Cross Reference Generator
 *
 *  written:       1997-08-03
 *  latest update: 1997-08-15 23:00:39
 *
 */

#ifndef __GG_xref__
#define __GG_xref__

#include <gg/ytree.h>
#include <gg/array.h>
#include <gg/floskel.h>

#ifndef UCHAR
#define UCHAR unsigned char
#endif

/* ------------------------------------------------------------------------ */
struct XREF_CONTEXT             /* definition section                       */
{
  struct YTREE
    *modules,                   /* dict of defined modules                  */
    *publics,                   /* dict of defined public symbols           */
    *bss;                       /* dict of defined BSS areas                */
} ;

/* ------------------------------------------------------------------------ */
struct XREF_RESOLVE             /* runtime section                          */
{
  struct XREF_CONTEXT *ctx;

  struct ARRAY_CONTROL
    *unresolved;                /* list of unresolved symbols               */

  struct YTREE
    *imported,                  /* dict of imported modules                 */
    *resolved,                  /* dict of resolved symbols                 */
    *not_found,                 /* dict of items that were not found        */
    *ignore;                    /* dict of ignored symbols                  */
} ;

/* ------------------------------------------------------------------------ */
struct XREF_MODULE
{
  char *name;
  char *object_name;
  struct XREF_CONTEXT *ctx;

  struct XREF_MODULE *shadows;  /* this module replaces or shadows another  */
  struct YTREE
    *externals,
    *publics,
    *bss;
} ;

/* ------------------------------------------------------------------------ */
struct XREF_PUBLIC
{
  char *name;
  struct XREF_MODULE *module;   /* module where symbol is defined           */

#ifdef NOT_USED
  struct YTREE *imported;       /* names of modules importing this symbol   */
#endif
} ;

/* ------------------------------------------------------------------------ */
#define xref_new_context() \
  ((struct XREF_CONTEXT *) calloc (sizeof (struct XREF_CONTEXT), 1))

/* ------------------------------------------------------------------------ */
/* %sbr/xref01.c */
struct XREF_MODULE *xref_module (struct XREF_CONTEXT *ctx, char *name,
  int replace);

int xref_set_object (struct XREF_MODULE *mod, char *name);
struct XREF_PUBLIC *xref_public (struct XREF_MODULE *mod, char *name);
int xref_external (struct XREF_MODULE *mod, char *name);

/* %sbr/xref02.c */
struct XREF_RESOLVE *xref_new_resolve (struct XREF_CONTEXT *ctx);
long xref_resolve (struct XREF_RESOLVE *res, char *name);
int xref_ignore (struct XREF_RESOLVE *res, char *name, void *cd);
/* internal functions, no need to call them directly */
int xref_print_ref_list (long info, char *str, void *cd);
int xref_resolve_symbols (struct YTREE *yt, char *str, void *cd);

/* %sbr/xref03.c */
int xref_do_resolve (struct XREF_RESOLVE *res, int show_resolved,
  int show_unresolved);

#endif /* __GG_xref__ */
