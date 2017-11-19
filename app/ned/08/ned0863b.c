/*
 *  FILE %ned/08/ned0863.c
 *
 *  preset a feature
 *
 *  written:       1997-06-16: extracted from ned0863.c
 *  latest update: 1999-04-25 16:33:45
 *  $Id: ned0863b.c,v 1.3 2010/05/04 02:47:07 gonter Exp $
 *
 */

#ifdef MSDOS
/* #pragma check_stack(off) */
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/filename.h>
#include <gg/tfb.h>
#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_wc_simple_feature_create (
struct WINDOWCTRL *wc,
struct LINE *lp,
int idx,
int what,                               /* type of tag to create            */
char *str)
{
  int ftr_segment_cnt= 1;               /* number of feature parts          */
  char *ftr_segment [5];

  if (wc == (struct WINDOWCTRL *) 0
      || lp == (struct LINE *) 0
      || idx < 0
     ) return -1;

  switch (what)
  {
    default:
      return -1;

    case Ftype_SGML_entity_string:
      ftr_segment [0]= str;
      what= Ftype_SGML_ENTITY;
      break;

    case Ftype_SGML_tag_string:
      ftr_segment [0]= str;
      what= Ftype_SGML_TAG;
      break;

    case Ftype_SGML_tag_string2:
      ftr_segment [0]= "<";
      ftr_segment [1]= str;
      ftr_segment [2]= ">";
      what= Ftype_SGML_TAG;
      ftr_segment_cnt= 3;
      break;
  }

  ned_feature_set (wc, lp, idx, what,
                   ftr_segment_cnt, (const char **) ftr_segment);

  /* T2D: wc does not have to be on display at this point any more */
  wd_displine (wc, lp, wc->cy, wc->ax, wc->bx);

  return 0;
}

