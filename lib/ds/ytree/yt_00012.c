/*
 *  FILE %ds/ytree/yt_00012.c
 *
 *  process a YTREE structure
 *
 *  see also: ytree_process_info ()
 *
 *  written:       1994-08-04
 *  latest update: 1996-06-22 10:02:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_process (
struct YTREE *yt,
YTREE_PROCESSOR *processor,
void *client_data)
{
  for (; yt != (struct YTREE *) 0; yt= yt->YT_next)
  {
    (*processor) (yt, client_data);

    if (yt->YT_down != (struct YTREE *) 0)
      ytree_process (yt->YT_down, processor, client_data);
  }

  return 0;
}
