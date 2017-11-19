/*
 *  FILE %ds/ytree/yt_00008.c
 *
 *  print a YTREE node
 *
 *  written:       1990 06 02
 *                 1991 03 16: Revision; AIX
 *  latest update: 1996-01-21 23:32:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_print_node (
FILE *fo,
struct YTREE *yt,
int indent)
{
  int i;
  char *cp;

  fprintf (fo, "%08lX (%4d) ", (long) yt, yt->YT_lng_str);

  fprintf (fo, "%4ld ", yt->YT_size);

  fprintf (fo, "0x%04X ", yt->YT_flags);
  for (i= 0; i < indent; i++) fputc (' ', fo);

  cp= (char *) yt->YT_str;
  for (i= yt->YT_lng_str; i > 0; i--) fputc (*cp++, fo);
  fputc ('\n', fo);

  return 0;
}
