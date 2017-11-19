/*
 *  include FILE <gg/lmd5.h>
 *
 *  Contents:
 *  - structures: LMD5_CONTROL
 *  - prototypes:
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-27  9:06:23
 *
 */

#ifndef __GG_lmd5__
#define __GG_lmd5__

#include <gg/floskel.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
struct LMD5_CONTROL
{
  struct IRDB_HANDLE *LMD5_db;
  struct IRDB_HANDLE *LMD5_words;
  struct IRDB_POS *LMD5_pos;
  char *LMD5_word_table [4];
  char *LMD5_docs_table [4];
  char *LMD5_info_table [4];
} ;

/* prototypes: ------------------------------------------------------------ */
/* 0001 */ struct LMD5_CONTROL *lmd5_create_control (char *fnm, int is_new);
/* 0002 */ long lmd5_increment_word_count (struct LMD5_CONTROL *l5,
             char *word, char *docid, long cnt);
#ifdef _FILE_DEFINED
/* 0003 */ int lmd5_process_stream (struct LMD5_CONTROL *l5, FILE *fi);
#endif /* _FILE_DEFINED */
/* 0004 */ long lmd5_increment_document_count (struct LMD5_CONTROL *l5,
             char *docid, char *fref_name, long fref_begin, long fref_end,
             char *date_string);
/* 0005 */ int lmd5_set_info_attribute_value (struct LMD5_CONTROL *l5,
             char *attribute_name, char *attribute_value);

#endif /* __GG_lmd5__ */
