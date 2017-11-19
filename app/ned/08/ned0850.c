/*
 *  FILE %ned/08/ned0850.c
 *
 *  written:       1991 06 02
 *  latest update: 1999-04-25 16:33:26
 *  $Id: ned0850.c,v 1.3 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct FEATURE *q_feature_set (
struct LINE *lp,                /* Zeile an die das Feature angehaengt wird */
int cpos,                       /* Spalte in der sich das Feature befindet  */
int feature_type,               /* Typ des Feature Records                  */
int t_cnt,                      /* number of ...                            */
const char *ftxt[])             /* string segments for feature ...          */
{
  struct FEATURE *f;            /* newly generated feature                  */

  if (lp == (struct LINE *) 0
      || (f= ned_new_feature (cpos, feature_type)) == (struct FEATURE *) 0
     )
    return (struct FEATURE *) 0;

  qq_insert_string_array (f->ftr_text_line, 0, ftxt, t_cnt, 1);

  ned_insert_feature (&lp->ftr, f);

  return f;
}
