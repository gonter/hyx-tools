/*
 *  FILE %ds/ytree/yt_00022.c
 *
 *  process a YTREE structure
 *
 *  see also: ytree_process ()
 *
 *  written:       1996-06-22
 *  latest update: 1996-06-22  9:59:49
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <gg/ytree.h>

/* ------------------------------------------------------------------------ */
int ytree_process_info (
struct YTREE *yt,
YTREE_INFO_PROCESSOR *processor,
void *client_data)
{
  long info;

  for (; yt != (struct YTREE *) 0; yt= yt->YT_next)
  {
    if ((yt->YT_flags & YTflag_EOW)
        && (info= yt->YT_info) != (long) 0
       )
      (*processor) (info, client_data);

    if (yt->YT_down != (struct YTREE *) 0)
      ytree_process_info (yt->YT_down, processor, client_data);
  }

  return 0;
}
