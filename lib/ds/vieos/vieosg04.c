/*
 *  FILE %ds/vieos/vieosg04.c
 *
 *  destroy a generic object in a hash tree
 *
 *  written:       1996-03-19
 *  latest update: 1996-03-19  9:32:00
 *
 */

#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
int vieos_destructor_generic (struct YTREE *yt, void *cd)
{
  VIEOS_DESTRUCTOR *destructor;

  if (yt == (struct YTREE *) 0
      || !(yt->YT_flags & YTflag_EOW)
      || (destructor= (VIEOS_DESTRUCTOR *) cd) == (VIEOS_DESTRUCTOR *) 0
     ) return 0;

  (*destructor) ((ClientData) yt->YT_info);

  return 0;
}
