/*
 *  FILE %ds/varspace/varsp004.c
 *
 *  variable space management
 *
 *  written:       1994-12-11
 *  latest update: 1996-01-21 23:41:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/varspace.h>

/* ------------------------------------------------------------------------ */
struct VAR_SPACE *vs_set_array (
struct YTREE **yt_root,
char *vsp_name [],
int vsp_cnt,
struct YTREE *vsp_array)
{
  struct VAR_SPACE *vs;

  if ((vs= vs_get_record (yt_root, vsp_name, vsp_cnt))
      != (struct VAR_SPACE *) 0)
  {
    vs->VS_array= vsp_array;
  }

  return vs;
}
