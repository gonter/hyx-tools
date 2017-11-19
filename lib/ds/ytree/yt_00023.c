/*
 *  FILE %ds/ytree/yt_00023.c
 *
 *  track a YTREE structure
 *  sse also: ytree_process
 *
 *  written:       1996-06-23
 *  latest update: 1996-12-01 22:06:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_track_info (
struct YTREE *yt,
char *buffer,
int buffer_size,
int buffer_pos,
YTREE_INFO_TRACKER *tracker,
void *client_data)
{
  int pfx_lng;                  /* length of current ytree prefix           */
  int str_lng;                  /* length of constructed string sofar       */
  long info;

  for (; yt != (struct YTREE *) 0; yt= yt->YT_next)
  {
    pfx_lng= yt->YT_lng_str;
    if (buffer_pos+pfx_lng > buffer_size)
    { /* oh, oh! */
      pfx_lng= buffer_size - buffer_pos-1;
    }

    str_lng= buffer_pos + pfx_lng;
    strncpy (buffer+buffer_pos, (char *) yt->YT_str, pfx_lng);
    buffer [str_lng]= 0;

    if ((yt->YT_flags & YTflag_EOW)
        && (info= yt->YT_info) != (long) 0
       )
      (*tracker) (info, buffer, client_data);

    if (yt->YT_down != (struct YTREE *) 0)
      ytree_track_info (yt->YT_down,
                   buffer, buffer_size, str_lng,
                   tracker, client_data);
  }

  return 0;
}
