/*
 *  FILE %ds/lmd5/lmd50002.c
 *
 *  LM/D Engine Version 5
 *
 *  written:       1996-04-14
 *  latest update: 1996-04-14 12:12:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lmd5.h>

/* ------------------------------------------------------------------------ */
long lmd5_increment_word_count (
struct LMD5_CONTROL *l5,
char *word,
char *docid,
long cnt)
/* wordcount.<word>.docs.<docid> += cnt; */
{
  struct IRDB_POS *ipos;
  long acc_cnt;

  if (l5 == (struct LMD5_CONTROL *) 0
      || (ipos= l5->LMD5_pos) == (struct IRDB_POS *) 0
     )
    return -1L;

  l5->LMD5_word_table [1]= word;
  l5->LMD5_word_table [2]= "docs";
  l5->LMD5_word_table [3]= docid;

  acc_cnt= irdb_dbg_post_increment_long (ipos, l5->LMD5_word_table, 4, cnt);

  l5->LMD5_word_table [1]= word;
  l5->LMD5_word_table [2]= "cnt";
  l5->LMD5_word_table [3]= "total";

  irdb_dbg_post_increment_long (ipos, l5->LMD5_word_table, 4, cnt);

  return acc_cnt;
}
