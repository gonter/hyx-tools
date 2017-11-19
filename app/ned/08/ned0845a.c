/*
 *  FILE %ned/08/ned0845a.c
 *
 *  deactivate a frame
 *
 *  written:       1996-03-16
 *  latest update: 1999-04-25 16:33:15
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_deactivate_frame (struct FRAMECTRL *fr)
{
  struct CLUSTERCTRL *cl;
  struct FRAMECTRL *fr2;
  struct FRAMECTRL **frp;

  if (fr == (struct FRAMECTRL *) 0
      || (cl= fr->cluster) == (struct CLUSTERCTRL *) 0
     )
    return -1;

  for (frp= &(cl->frames);
       (fr2= *frp) != (struct FRAMECTRL *) 0;
       frp= &fr2->next)
  {
    if (fr2 == fr)
    { /* we have found the frame in the list of the cluster's frames */
      *frp= fr->next;
      break;
    }
  }

  free_or_what (fr->frame_name);
  free (fr);

  return 0;
}
