/*
 *  FILE ~/usr/nl_kr/lib/nl_00120.c
 *
 *  print veronica style results
 *
 *  written:       1993-05-01
 *                 1994-08-01: isolated from print_veronica_hit_list
 *  latest update: 1995-07-16
 *
 */

#include <stdio.h>
#include <gg/lookup.h>
#include <gg/sbr.h>

/* ------------------------------------------------------------------------ */
int lmd_print_veronica_docinfo_list (
FILE *fo,
FILE *vf,
struct DOCUMENT_INFO_LIST *start)
{
  long offset;
  int lines= 0;
  struct DOCUMENT_INFO *di;

  for (;
       start != (struct DOCUMENT_INFO_LIST *) 0; 
       start= start->DIL_next)
  {
    if ((di= start->DIL) == (struct DOCUMENT_INFO *) 0) continue;

    offset= di->DI_document_id -1L;
    fseek (vf, offset, 0L);

#ifdef DEBUG
    printf ("nl_00120: offset=%ld (0x%08lX)\n", offset, offset);
#endif

    ftransfer_line (vf, fo, 0x7FFFFFFFL);
    lines++;
  }

  return lines;
}
