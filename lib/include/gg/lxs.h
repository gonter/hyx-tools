/*
 *  include FILE <gg/lxs.h>
 *
 *  lexicon services
 *
 *  written:       1994-03-27
 *  latest update: 1995-07-18
 *
 */

#ifndef __GG_lxs__
#define __GG_lxs__

#include <gg/floskel.h>
#include <gg/lookup.h>
#include <gg/attlist.h>

/* ------------------------------------------------------------------------ */
struct LXS_OLD_ENTRY
{
#ifdef JUNK
  struct WORD_REF *lxs_word_ref;
  struct ATTRIBUTE_LIST *lxs_attribute_list;
#endif
  struct LXS_OLD_ENTRY *lxs_next;
  long lxs_entry_type;
#define LXS_ty_undef    0
#define LXS_ty_word_ref 1
#define LXS_ty_attlist  2
#define LXS_ty_raw      3
  long lxs_entry_size;          /* length of entry memory block             */
  void *lxs_entry;
} ;

#ifdef __COMMENT__
The client for the Lexicon Services can specify which kind of information
is wanted, e.g.
1. if the word_ref information should be returned,
2. if the attribute list should be filled with (selected) attributes
3. if the full lexicon entry should be placed in the lxs_entry buffer.

Also, the origin of the data may also be configured, e.g.
+  from a word_ref table
+  from a lexicon file
+  from a lexicon server (TBS)

#endif /* __COMMENT__ */

/* ------------------------------------------------------------------------ */
struct LXS_ENTRY
{ /* derived from struct WORD_REF */

  /* quick'n'dirty mini lexicon for special processing actions              */
  long LXSE_language;           /* one language of that word                */
  long LXSE_fq_rank;            /* frequency ranking (for stop word thsld)  */
  long LXSE_word_type;          /* bit field for word types                 */
  long LXSE_interpretation;     /* interpretation code within programs      */
  long LXSE_bin_lex_offset;     /* offset in binary lexicon                 */
} ;

/* ------------------------------------------------------------------------ */
#ifdef _FILE_DEFINED
#define _LXS_CONTROL_DEFINED
struct LXS_CONTROL
{
  int LXSC_type;

  /* cluster file */
  FILE *LXSC_hyx;
  FILE *LXSC_idx;
  FILE *LXSC_lut;
  FILE *LXSC_xfn;
} ;
#endif /* _FILE_DEFINED */

#define LXSC_TYPE_undefined     0
#define LXSC_TYPE_cluster       1

/* lxs_0001.c ------------------------------------------------------------- */
struct LXS_OLD_ENTRY *cdecl lxs_get_word (int lexicon_number,
  unsigned char *wrd, int cr_flag);
int cdecl lxs_set_word_ref (int lexicon_number, char *fnm_lut, char *fnm_wr);
int cdecl lxs_shutdown_word_ref (int lexicon_number);
int cdecl lxs_intialize (int num);


#endif /* __GG_lxs__ */
