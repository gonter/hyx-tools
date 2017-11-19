/*
 *  FILE %ned/08/ned0885b.c
 *
 *  written:       1996-07-01
 *  latest update: 1998-08-15 12:37:04
 *  $Id: ned0885b.c,v 1.2 2002/06/15 04:35:21 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include "ed.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
void ned_set_lookup_tag_fr ()
{
  ned_wc_feature_create (aw, Ftype_lookup_fr, FTR_EDIT_ATTRIBUTE, "fr=");
}

/* ------------------------------------------------------------------------ */
void ned_set_lookup_tag_fr2 ()
{
  ned_wc_feature_create (aw, Ftype_lookup_fr2, FTR_EDIT_ATTRIBUTE, "fr=");
}
