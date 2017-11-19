/*
 *  FILE %ned/08/ned0864.c
 *
 *  create the contents of an otherwise empty frame
 *
 *  written:       1991 07 05
 *  latest update: 1999-05-12 12:03:22
 *  $Id: ned0864.c,v 1.7 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern char *ned_renamed_object;

#define NEW_COLOUR (WV_GELB|WH_BRAUN)

/* ------------------------------------------------------------------------ */
int initialize_frame (struct WINDOWCTRL *w, const char *fr_name)
{
  struct LINE *l2, *l1;
  struct FEATURE *f;
  const char *frame_begin [3] = { "<Frame ", (char *) 0, ">" } ;
  const char *frame_end   [2] = { "</Frame>", (char *) 0 } ;

  if (w == (struct WINDOWCTRL *) 0
      || (l2= alloc_line ()) == (struct LINE *) 0
      || (l1= alloc_line ()) == (struct LINE *) 0
     )
     return -1;

  /* duplicated code from ned_rename_object () */
  if (ned_renamed_object == (char *) 0)
  {
    if ((ned_renamed_object= malloc (MAX_FNM_LENGTH)) == (char *) 0)
      return -1;

    ned_renamed_object [0]= 0;
  }

  qq_insert_string (l2, 0, frame_end [0], 8, 1);
  frame_begin [1]= fr_name;
  strcpy_max (ned_renamed_object, fr_name, MAX_FNM_LENGTH);

  if (w->file_format == FMT_SGML)
  {
    if ((f= q_feature_set (l2, 0, Ftype_SGML_TAG, 1, frame_end))
            != (struct FEATURE *) 0) 
    {
      f->ftr_display_mode= FTR_display_replarray;
      f->ftr_replarray_size= 8;
      f->ftr_colour= NEW_COLOUR;
    }

    qq_insert_string (l1, 0, "<Frame>", 7, 1);

    if ((f= q_feature_set (l1, 0, Ftype_SGML_TAG, 3, frame_begin))
            != (struct FEATURE *) 0) 
    {
      f->ftr_display_mode= FTR_display_replarray;
      f->ftr_replarray_size= 7;
      f->ftr_colour= NEW_COLOUR;
    }
  }
  else
  {
    qq_insert_string_array (l1, 0, frame_begin, 3, 1);
  }

  l2->prev= l1;
  l1->next= l2;

  w->WC_act= w->WC_first= l1;
  w->znr= 1;
  w->cx= w->ax;
  w->cy= w->ay;
  w->hv= 0;
  w->ins_flg= INSFLG_insert;
  w->f_upd= 1;


  return 0;
}
