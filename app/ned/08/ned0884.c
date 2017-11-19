/*
 *  FILE %ned/08/ned0884.c
 *
 *  written:       1994-04-10
 *  latest update: 1998-08-15 12:43:13
 *  $Id: ned0884.c,v 1.2 2005/07/08 17:00:42 gonter Exp $
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
void ned_set_mark ()
{
  ned_wc_feature_create (aw, Ftype_mark, FTR_EDIT_ATTRIBUTE, "name=");
  /* p_link_feature (); */
}
