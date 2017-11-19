/*
 *  FILE %ds/strings/str_0032.c
 *
 *  written:       1994-05-27 (extracted from ~/usr/obj/crf.c)
 *  latest update: 1996-04-14 12:58:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/strings.h>

/* ------------------------------------------------------------------------ */
void blanks (FILE *fo, int cnt)
{
  while (cnt-- > 0) fputc (' ', fo);
}
