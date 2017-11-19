/*
 *  include FILE <gg/lxs2.h>
 *
 *  lexicon services
 *
 *  written:       1996-12-20
 *  latest update: 1996-12-20  0:24:10
 *
 */

#ifndef __GG_lxs2__
#define __GG_lxs2__

#include <gg/floskel.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
struct LEXICON_ENTRY
{
  char *entry;
  int is_lower;                 /* 1: record is for lower case version      */

  struct LEXICON_ENTRY *lower_case;     /* same entry in lower case         */
  struct LEXICON_ENTRY *alt;    /* alternative mixed case version           */

  long ref_count;
} ;

/* ------------------------------------------------------------------------ */
struct LEXICON_CONTEXT
{
  char *name;

  struct YTREE *lower_case;
  struct YTREE *mixed_case;

  int to_lower;                 /* 1: record only lower case version        */

  long num_entries_lower;
  long num_entries_mixed;
} ;

/* ------------------------------------------------------------------------ */

/* buildup */
struct LEXICON_CONTEXT *lxs_new_context (char *name);

struct LEXICON_ENTRY *lxs_record (struct LEXICON_CONTEXT *lxc, char *word,
   int is_mixed);


/* diagnostics */

#ifdef _FILE_DEFINED
int lxs_dump_context (struct LEXICON_CONTEXT *lxc, FILE *fo);
int lxs_dump_entry (struct LEXICON_ENTRY *lxe, FILE *fo);
#endif /* _FILE_DEFINED */

int lxs_dump_entry2 (long entry_ref, void *cd);

#endif /* __GG_lxs2__ */
