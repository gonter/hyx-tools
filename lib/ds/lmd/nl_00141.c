/*
 *  FILE %ds/lmd/nl_00141.c
 *
 *  methods for the WRL object
 *
 *  written:       2002-02-03
 *  latest update: 2002-02-03  1:40:25
 *  $Id: nl_00141.c,v 1.1 2002/02/04 08:13:08 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
long WRL_index (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL_index;
  return 0L;
}

/* ------------------------------------------------------------------------ */
char *WRL_string (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL_string;
  return (char *) 0;
}

/* ------------------------------------------------------------------------ */
long WRL_count (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL.WR_count;
  return 0L;
}

/* ------------------------------------------------------------------------ */
long WRL_offset (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL.WR_docinfo_offset;
  return 0L;
}

/* ------------------------------------------------------------------------ */
long WRL_docs (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL.WR_docinfo_count;
  return 0L;
}

/* ------------------------------------------------------------------------ */
DIL *WRL_DIL (WRL *p)
{
  if (p != (WRL *) 0) return p->WRL_dil;
  return (DIL *) 0;
}
