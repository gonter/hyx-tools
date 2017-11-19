/*
 *  FILE %nl_kr/lib/nl_00117.c
 *
 *  print a document hit list
 *
 *  written:       1993-02-28
 *  latest update: 1995-12-05
 *  $Id: nl_00117.c,v 1.3 2002/01/29 08:01:42 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_print_doc_hit_list_stdout (
struct WORD_REF_LIST *wrl,
int print_dil)
{
  lmd_print_doc_hit_list (stdout, wrl, print_dil);
}

/* ------------------------------------------------------------------------ */
int lmd_print_doc_hit_list (
FILE *fo,
struct WORD_REF_LIST *wrl,
int print_dil)
{
  struct DOCUMENT_INFO_LIST *start;

  for (; wrl != (struct WORD_REF_LIST *) 0; wrl= wrl->WRL_next)
  {
    printf ("\n--------------------\n");
    printf ("word: %s\n", wrl->WRL_string);
    lmd_print_word_ref_info (fo, &wrl->WRL);

    if (print_dil && (start= wrl->WRL_dil) != (struct DOCUMENT_INFO_LIST *) 0)
      lmd_print_document_info_list (fo, wrl->WRL_dil);
  }

  return 0;
}
