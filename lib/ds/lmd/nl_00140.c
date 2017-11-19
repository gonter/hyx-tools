/*
 *  FILE %ds/lmd/nl_00140.c
 *
 *  create a query set object
 *
 *  written:       2002-01-20
 *  latest update: 2002-02-03  1:40:40
 *  $Id: nl_00140.c,v 1.2 2010/05/04 02:47:07 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
LMDQS *new_LMDQS (char *fnm)
{
  struct LMD_QUERY_SET *p;
  if ((p= lmd_new_query_set ()) == (struct LMD_QUERY_SET *) 0)
  {
ERROR:
    return (struct LMD_QUERY_SET *) 0;
  }

  lmd_qs_setup_table_names (p, fnm);
  if (lmd_deref_init (p) != 0)
  {
    free (p);
    goto ERROR;
  }

  return p;
}
