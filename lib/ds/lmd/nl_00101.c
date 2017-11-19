/*
 *  FILE ~/usr/nl_kr/lib/nl_00101.c
 *
 *  find a document in a list
 *
 *  written:       1993-02-28
 *  latest update: 1995-07-22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO_LIST *lmd_find_document_info_list (
struct DOCUMENT_INFO_LIST *start,
long doc_id)
{
  for (; start != (struct DOCUMENT_INFO_LIST *) 0; start= start->DIL_next)
    if (start->DIL->DI_document_id == doc_id) return start;

  return (struct DOCUMENT_INFO_LIST *) 0;
}
