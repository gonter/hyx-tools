/*
 *  FILE 1996-01-21 23:32:03
 *
 *  print a YTREE node
 *
 *  written:       1990 06 02
 *  latest update: 1996-01-21 23:32:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_print (FILE *fo, struct YTREE *yt, int indent)
{
  for (; yt != (struct YTREE *) 0; yt= yt->YT_next)
  {
    ytree_print_node (fo, yt, indent);
    if (yt->YT_down != (struct YTREE *) 0)
       ytree_print (fo, yt->YT_down, indent+yt->YT_lng_str);
  }

  return 0;
}
