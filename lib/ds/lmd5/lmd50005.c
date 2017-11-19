/*
 *  FILE %ds/lmd5/lmd50005.c
 *
 *  LM/D Engine Version 5
 *
 *  written:       1996-04-14
 *  latest update: 1996-05-06  0:16:09
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/lmd5.h>

/* ------------------------------------------------------------------------ */
int lmd5_set_info_attribute_value (
struct LMD5_CONTROL *l5,
char *attribute_name,
char *attribute_value)
/* info.<attribute>= <value> */
{
  struct IRDB_POS *ipos;

  if (l5 == (struct LMD5_CONTROL *) 0
      || (ipos= l5->LMD5_pos) == (struct IRDB_POS *) 0
     )
    return -1;

  l5->LMD5_info_table [1]= attribute_name;

printf ("\n****************\n");

  return irdb_dbg_replace_string (ipos, l5->LMD5_info_table, 2, attribute_value);
}
