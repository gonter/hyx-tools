/*
 *  include FILE <gg/objutils.h>
 *
 *  written:       1994-05-28
 *  latest update: 1994-12-08
 *
 */


#ifndef __GG_objutils__
#define __GG_objutils__

#include <gg/floskel.h>

#ifdef NIL
#undef NIL
#endif
#define NIL ((void *) 0)

/* ------------------------------------------------------------------------ */
struct MODULE
{
  struct MODULE *next;
  void *sym_list, **next_sym;
  void *ext_list, **next_ext;
  char *title;
  char *file_name;
  char *translator;
  char *library;
} ;

/* ------------------------------------------------------------------------ */
struct SYMBOL
{
  struct SYMBOL *next;
  struct SYMBOL *next_sym;
  struct MODULE *mod;
  void *ext_list;               /* Liste der externen Module, die dieses    */
                                /* Symbol verwenden                         */
  char *sym_name;
  int   typ;
} ;

/* ------------------------------------------------------------------------ */
struct EXTERN
{
  struct EXTERN *next;
  struct EXTERN *next_ext;
  struct EXTERN *next_ext2;     /* nach Modul-Titel verkettet               */
  struct MODULE *mod;
  struct SYMBOL *sym;
  int    local;
} ;

/* ------------------------------------------------------------------------ */
struct ARIADNE
{
  struct ARIADNE *ar_up;
  struct EXTERN *ar_ex;
  struct SYMBOL *ar_sy;
} ;

/* Prototypes: ------------------------------------------------------------ */
/* crf01.c */ struct MODULE *cdecl find_module (char *s, struct MODULE **pp);
/* crf02.c */ struct SYMBOL *cdecl find_symbol (char *s, int mode,
                struct SYMBOL **pp, struct MODULE *akt_symbol);
/* crf03.c */ struct SYMBOL *cdecl find_local_symbol (struct SYMBOL *p,
                 char *s);
/* crf04.c */ void cdecl sort_extern (struct EXTERN **pep, struct EXTERN *ep, int mode);
/* crf05.c */ struct MODULE *cdecl get_module (void);
/* crf05.c */ struct SYMBOL *cdecl get_symbol (void);
/* crf05.c */ int cdecl crf (char *fn, int read_object, char *tmp_file);
#ifdef _FILE_DEFINED
/* crf06.c */ void cdecl print_modules (FILE *fo, struct MODULE *module);
/* crf07.c */ void cdecl print_symbols (FILE *fo, struct SYMBOL *symbol,
                int MAX_LINE);
/* crf08.c */ int cdecl print_crf_tree (FILE *fo, char *symb,
                 struct SYMBOL *symbol);
/* crf09.c */ int cdecl print_crf_symbol (FILE *fo, int indent,
                struct SYMBOL *sp, struct ARIADNE *arp);
#endif

#endif /* __GG_objutils__ */
