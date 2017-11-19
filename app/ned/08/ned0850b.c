/*
 *  FILE %ned/08/ned0850b.c
 *
 *  written:       1996-07-25
 *  latest update: 1999-04-25 16:33:31
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FEATURE *ned_new_feature (int cpos, int feature_type)
{
  struct FEATURE *f;

  if ((f= ned_feature_alloc ()) == (struct FEATURE *) 0
      || (f->ftr_text_line= alloc_line ()) == (struct LINE *) 0
     )
    return (struct FEATURE *) 0;

  f->ftr_pos=            cpos;
  f->ftr_type=           feature_type;
  f->ftr_display_mode=   FTR_display_point;
  f->ftr_replarray_size= 1;
  f->ftr_colour=         COL_DEF_FEATURE;
  f->ftr_duplication=    FTR_dup_allways;

  return f;
}
