/*
 *  FILE %ds/varspace/varsp003.c
 *
 *  variable space management
 *
 *  written:       1994-12-11
 *  latest update: 1996-08-08 17:06:56
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/varspace.h>

/* ------------------------------------------------------------------------ */
struct VAR_SPACE *vs_set (
struct YTREE **yt_root,
char *vsp_name [],
int vsp_cnt,
long vsp_type,
long vsp_value)
{
  struct VAR_SPACE *vs;

  if ((vs= vs_get_record (yt_root, vsp_name, vsp_cnt))
      != (struct VAR_SPACE *) 0)
  {
    vs->VS_type= vsp_type;
    vs->VS_value= (void *) vsp_value;
  }

  return vs;
}
