/*
 *  FILE %ds/varspace/varsp001.c
 *
 *  variable space management
 *
 *  written:       1994-12-11
 *  latest update: 1996-08-08 17:08:28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/varspace.h>

/* ------------------------------------------------------------------------ */
struct VAR_SPACE *vs_get_record (
struct YTREE **yt_root,
char *vsp_name [],
int vsp_cnt)
{
  struct VAR_SPACE *vs= (struct VAR_SPACE *) 0;
  struct YTREE *yt;
  int vsp_num;

  for (vsp_num= 0; vsp_num < vsp_cnt; vsp_num++)
  {
    if ((yt= ytree_insert_word (yt_root, (unsigned char *) vsp_name[vsp_num]))
        == (struct YTREE *) 0) return (struct VAR_SPACE *) 0;

    if (yt->YT_flags & YTflag_EOW)
    {
      vs= (struct VAR_SPACE *) yt->YT_info;
    }
    else
    { /* this variable doesn't exist sofar */
      if ((vs= (struct VAR_SPACE *) calloc (sizeof (struct VAR_SPACE), 1))
          == (struct VAR_SPACE *) 0) goto STOP;

      vs->VS_signature= SIG_VS_NODE;
      yt->YT_flags |= YTflag_EOW;
      yt->YT_info= (long) vs;
    }

    yt_root= &(vs->VS_array);
  }

STOP:
  return vs;
}
