/*
 *  FILE %ds/irdb/irdb0026.c
 *
 *  irrelational database
 *  called as a YTREE_PROCESSOR method
 *
 *  written:       1996-05-05
 *  latest update: 1996-05-05 12:09:30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/ytree.h>
#include <gg/irdb.h>

/* ------------------------------------------------------------------------ */
int irdb_restore_handle (
struct YTREE *yt_node,
void *client_data)
{
  FILE *fi;
  struct IRDB_HANDLE *hnd;

  if (yt_node != (struct YTREE *) 0
      && (yt_node->YT_flags & YTflag_EOW)
      && (fi= (FILE *) client_data) != (FILE *) 0
     )
  {
    fseek (fi, yt_node->YT_info, 0);
    hnd= irdb_load_handle (fi);
    yt_node->YT_info= (long) hnd;
  }

  return 0;
}
