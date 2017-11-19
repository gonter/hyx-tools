/*
 *  FILE %ds/lmd/nl_00142.c
 *
 *  methods for the DIL object
 *
 *  written:       2002-02-03
 *  latest update: 2002-02-03  1:40:25
 *  $Id: nl_00142.c,v 1.1 2002/02/04 08:13:08 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
DIL *DIL_next (DIL *p)
{
  if (p == (DIL *) 0) return (DIL *) 0;
  return p->DIL_next;
}

/* ------------------------------------------------------------------------ */
long DIL_document_id (DIL *p)
{
  if (p == (DIL *) 0 || p->DIL == (struct DOCUMENT_INFO *) 0) return 0L;
  return p->DIL->DI_document_id;
}

/* ------------------------------------------------------------------------ */
long DIL_hit_count (DIL *p)
{
  if (p == (DIL *) 0 || p->DIL == (struct DOCUMENT_INFO *) 0) return 0L;
  return p->DIL->DI_hit_count;
}

/* ------------------------------------------------------------------------ */
long DIL_document_ptr (DIL *p)
{
#ifdef LMD_EXTENDED_MODEL
  if (p == (DIL *) 0 || p->DIL == (struct DOCUMENT_INFO *) 0) return 0L;
  return p->DIL->DI_document_ptr;
#else
  return 0L;
#endif /* LMD_EXTENDED_MODEL */
}

/* ------------------------------------------------------------------------ */
long DIL_pos (DIL *p, int idx)
{
#ifdef LMD_EXTENDED_MODEL
  if (p == (DIL *) 0
      || p->DIL == (struct DOCUMENT_INFO *) 0
      || idx >= MAX_DI_POS
     ) return 0L;

  return p->DIL->DI_pos [idx];
#else
  return 0L;
#endif /* LMD_EXTENDED_MODEL */
}
