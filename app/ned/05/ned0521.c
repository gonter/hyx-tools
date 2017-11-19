/*
 *  FILE %ned/05/ned0521.c
 *
 *  written:       1991 07 10: Revision
 *  latest update: 1999-04-25 16:31:53
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <memory.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_copy_feature_list (
struct FEATURE **fd,            /* Feature Destination                      */
struct FEATURE *fs)             /* Feature Source                           */
/* Return  0 ... ok                                                         */
/*        -1 ... Error                                                      */
{
  struct FEATURE *fn;           /* Feature New                              */

  while (fs != (struct FEATURE *) 0)
  {
    if (1 /* TEST: COPY_FEATURE  fs->ftr_duplication & FTR_dup_copy */)
    {
      if ((fn= ned_feature_alloc ()) == (struct FEATURE *) 0) return -1;

      /* Achtung: memcpy geht nur, wenn die Struktur nicht veraendert wird! */
      memcpy (&fn->ftr_pos, &fs->ftr_pos,
              sizeof (struct FEATURE)-4*sizeof (void *));

      if (fs->ftr_duplication & FTR_dup_copy)
        ned_copy_line ((struct LINE **) &fn->ftr_text_line,
                       (struct LINE *) fs->ftr_text_line);

      *fd= fn;
       fd= &fn->ftr_next;
     }
     fs= fs->ftr_next;
  }

  return 0;
}
