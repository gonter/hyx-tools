/*
 *  FILE %ds/irdb/irdb0027.c
 *
 *  irrelational database
 *  called as a YTREE_PROCESSOR method
 *
 *  written:       1996-05-06
 *  latest update: 1996-05-06  0:25:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_restore_strings (
struct YTREE *yt_node,
void *client_data)
{
  FILE *fi;
  char *str;

  if (yt_node != (struct YTREE *) 0
      && (yt_node->YT_flags & YTflag_EOW)
      && (fi= (FILE *) client_data) != (FILE *) 0
     )
  {
    fseek (fi, yt_node->YT_info, 0);
    str= irdb_load_string (fi, (char *) 0, 0);
    yt_node->YT_info= (long) str;
  }

  return 0;
}
