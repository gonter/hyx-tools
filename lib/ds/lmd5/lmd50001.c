/*
 *  FILE %ds/lmd5/lmd50001.c
 *
 *  LM/D Engine Version 5
 *
 *  written:       1996-04-14
 *  latest update: 1996-05-28 19:47:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <gg/irdb.h>
#include <gg/lmd5.h>

/* ------------------------------------------------------------------------ */
struct LMD5_CONTROL *lmd5_create_control (char *fnm, int is_new)
{
  struct LMD5_CONTROL *l5= (struct LMD5_CONTROL *) 0;
  struct IRDB_HANDLE *ihw;
  struct IRDB_POS *ipos;

  if ((l5= (struct LMD5_CONTROL *) calloc (sizeof (struct LMD5_CONTROL), 1))
        != (struct LMD5_CONTROL *) 0
      && (ipos= irdb_new_pos (fnm, "lmd5", is_new)) != (struct IRDB_POS *) 0
     )
  {
    l5->LMD5_pos= ipos;

    l5->LMD5_db= ipos->IRDB_handle;
    l5->LMD5_word_table [0]= "wordcount";
    l5->LMD5_docs_table [0]= "docs";
    l5->LMD5_info_table [0]= "info";

    /* get the subtree for the word info */
    if ((ihw= irdb_locate_handle (ipos, l5->LMD5_word_table, 1,
                                  1, (long) IRDBty_struct))
          != (struct IRDB_HANDLE *) 0
       )
    {
      l5->LMD5_words= ihw;
      return l5;
    }
  }

  return (struct LMD5_CONTROL *) 0;
}
