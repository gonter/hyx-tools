/*
 *  FILE %ds/varspace/varsp002.c
 *
 *  variable space management
 *
 *  written:       1994-12-11
 *  latest update: 1996-08-08 17:08:16
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/varspace.h>

/* ------------------------------------------------------------------------ */
struct VAR_SPACE *vs_get (
struct YTREE *yt_root,
char *vsp_name [],
int vsp_cnt)
{
  struct VAR_SPACE *vs= (struct VAR_SPACE *) 0;
  struct YTREE *yt;
  int vsp_num;

  for (vsp_num= 0; vsp_num < vsp_cnt; vsp_num++)
  {
    if ((yt= ytree_lookup_word (yt_root, (unsigned char *) vsp_name[vsp_num]))
             == (struct YTREE *) 0
        || !(yt->YT_flags & YTflag_EOW)
       )
       return (struct VAR_SPACE *) 0;

    vs= (struct VAR_SPACE *) yt->YT_info;
    yt_root= vs->VS_array;
  }

  return vs;
}
