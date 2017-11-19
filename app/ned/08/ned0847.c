/*
 *  FILE %ned/08/ned0847.c
 *
 *  Frame Control Struktur im angegebenen Cluster eintragen  
 *
 *  written:       1991 05 29
 *  latest update: 1999-04-25 16:33:22
 *  $Id: ned0847.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FRAMECTRL *create_framectrl (
struct CLUSTERCTRL *cl,
const char *fr_name,
long idx,
int where)
{
  struct FRAMECTRL *fc;

  if ((fc= (struct FRAMECTRL *) calloc (sizeof (struct FRAMECTRL), 1))
      == (struct FRAMECTRL *) 0) return (struct FRAMECTRL *) 0;

  fc->next= (cl == (struct CLUSTERCTRL *) 0)
            ? (struct FRAMECTRL *) 0
            : cl->frames;

  if (cl != (struct CLUSTERCTRL *) 0) cl->frames= fc;

  fc->cluster= cl;
  fc->frame_name= strdup (fr_name);
  fc->frame_index= idx;
  fc->frame_lookup= where;
  fc->frame_status= FRAME_is_unindexed;

  return fc;
}
