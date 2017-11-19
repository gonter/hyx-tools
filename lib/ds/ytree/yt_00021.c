/*
 *  FILE %ds/ytree/yt_00021.c
 *
 *  track a YTREE structure
 *  sse also: ytree_process
 *
 *  written:       1996-04-06
 *  latest update: 1996-08-08 16:35:41
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_track (
struct YTREE *yt,
char *buffer,
int buffer_size,
int buffer_pos,
YTREE_TRACKER *tracker,
void *client_data)
{
  int pfx_lng;                  /* length of current ytree prefix           */
  int str_lng;                  /* length of constructed string sofar       */

  for (; yt != (struct YTREE *) 0; yt= yt->YT_next)
  {
    pfx_lng= yt->YT_lng_str;
    if (buffer_pos+pfx_lng > buffer_size)
    { /* oh, oh! */
      pfx_lng= buffer_size-buffer_pos-1;
    }

    str_lng= buffer_pos + pfx_lng;
    strncpy (buffer+buffer_pos, (char *) yt->YT_str, pfx_lng);
    buffer [str_lng]= 0;

    (*tracker) (yt, buffer, client_data);

    if (yt->YT_down != (struct YTREE *) 0)
      ytree_track (yt->YT_down,
                   buffer, buffer_size, str_lng,
                   tracker, client_data);
  }

  return 0;
}
