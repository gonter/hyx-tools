/*
 *  FILE %ds/lmd5/lmd50004.c
 *
 *  LM/D Engine Version 5
 *
 *  written:       1996-04-14
 *  latest update: 1996-05-19 10:30:32
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lmd5.h>

/* ------------------------------------------------------------------------ */
long lmd5_increment_document_count (
struct LMD5_CONTROL *l5,
char *docid,
char *fref_name,
long fref_begin,
long fref_end,
char *date_string)
/* docs.<docid>.cnt.upd++ */
{
  struct IRDB_POS *ipos;
  long cnt;

  if (l5 == (struct LMD5_CONTROL *) 0
      || (ipos= l5->LMD5_pos) == (struct IRDB_POS *) 0
     )
    return -1L;

  l5->LMD5_docs_table [1]= docid;
  l5->LMD5_docs_table [2]= "cnt";
  l5->LMD5_docs_table [3]= "upd";

printf ("\n***** 50004 *****\n");

  irdb_dbg_post_increment_long (ipos, l5->LMD5_docs_table, 4, 1L);

  if (fref_name != (char *) 0)
  { 
    l5->LMD5_docs_table [3]= "begin";
    irdb_dbg_set_long (ipos, l5->LMD5_docs_table, 4, fref_begin);

    l5->LMD5_docs_table [3]= "end";
    irdb_dbg_set_long (ipos, l5->LMD5_docs_table, 4, fref_end);

    l5->LMD5_docs_table [2]= "fref";
    l5->LMD5_docs_table [3]= "name";
    irdb_dbg_replace_string (ipos, l5->LMD5_docs_table, 4, fref_name);

    if (date_string != (char *) 0)
    {
      l5->LMD5_docs_table [3]= "name";
      irdb_dbg_replace_string (ipos, l5->LMD5_docs_table, 4, date_string);
    }
  }

  return cnt;
}
