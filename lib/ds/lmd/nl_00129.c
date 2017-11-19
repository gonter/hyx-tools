/*
 *  FILE ~/usr/nl_kr/lib/nl_00129.c
 *
 *  construct a TERM structure
 *
 *  written:       1994-08-27
 *  latest update: 1995-07-31
 *
 */

#ifdef DEBUG
#include <stdio.h>
#endif /* DEBUG */

#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO_LIST *lmd_dil_accumulate (struct WORD_REF_LIST *wrl)
{
  struct DOCUMENT_INFO_LIST *dil= (struct DOCUMENT_INFO_LIST *) 0;

  for (; wrl != (struct WORD_REF_LIST *) 0; wrl= wrl->WRL_next)
  {
#ifdef DEBUG
printf ("=========================\n");
printf ("accumulator:\n");
lmd_print_document_info_list (stdout, dil);
printf ("-------------------------\n");
printf ("add:\n");
lmd_print_document_info_list (stdout, wrl->WRL_dil);
printf ("-------------------------\n");
#endif /* DEBUG */

   dil= lmd_dil_operator (dil, wrl->WRL_dil, (long) WRint_logic_or);

#ifdef DEBUG
printf ("result:\n");
lmd_print_document_info_list (stdout, dil);
printf ("=========================\n");
#endif /* DEBUG */
  }

  return dil;  
}
