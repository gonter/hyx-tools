/*
 *  FILE ~/usr/nl_kr/lib/nl_00134.c
 *
 *  create a list of document info nodes by traversing a YTREE
 *
 *  written:       1995-07-22
 *  latest update: 1995-07-31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#ifdef DEBUG
#include <stdio.h>
#endif

#include <stdlib.h>
#include <gg/ytree.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
int lmd_create_dil (struct YTREE *yt, void *client_data)
{
  struct DEREF_CONTROL *dc;
  struct DOCUMENT_INFO_LIST *dil;

  if (yt == (struct YTREE *) 0) return -1;
  if (!(yt->YT_flags & YTflag_EOW)) return 0;
  
  if ((dc= (struct DEREF_CONTROL *) client_data)
         == (struct DEREF_CONTROL *) 0
      || (dil= lmd_new_document_info_list())
         == (struct DOCUMENT_INFO_LIST *) 0)
    return -1;

#ifdef DEBUG
  printf ("nl_00134: info=%ld (0x%08lX) flags=0x%04X\n",
          yt->YT_info, yt->YT_info, yt->YT_flags);
#endif

  dil->DIL= (struct DOCUMENT_INFO *) yt->YT_info;
  *dc->DC_dil_app= dil;
   dc->DC_dil_app= &dil->DIL_next;

  return 0;
}
