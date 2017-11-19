/*
 *  FILE %ds/lmd/nl_00130.c
 *
 *  duplicate a TERM structure
 *
 *  written:       1994-08-27
 *  latest update: 1995-07-31
 *  $Id: nl_00130.c,v 1.3 2001/08/03 15:51:42 gonter Exp $
 *
 */

#include <stdlib.h>
#ifndef __GG_CMS__
#include <memory.h>
#endif
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO_LIST *lmd_dil_dup (struct DOCUMENT_INFO_LIST *org)
{
  struct DOCUMENT_INFO_LIST *dup;

  if ((dup= (struct DOCUMENT_INFO_LIST *) malloc (
            sizeof (struct DOCUMENT_INFO_LIST)))
      != (struct DOCUMENT_INFO_LIST *) 0)
  {
    dup->DIL= lmd_di_dup ((struct DOCUMENT_INFO *) org->DIL);
    dup->DIL_next= (struct DOCUMENT_INFO_LIST *) 0;
  }

  return dup;
}

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO *lmd_di_dup (struct DOCUMENT_INFO *org)
{
  struct DOCUMENT_INFO *dup;

  if ((dup= (struct DOCUMENT_INFO *) malloc (
            sizeof (struct DOCUMENT_INFO)))
      != (struct DOCUMENT_INFO *) 0)
  {
    memcpy (dup, org, sizeof (struct DOCUMENT_INFO));
  }

  return dup;
}
