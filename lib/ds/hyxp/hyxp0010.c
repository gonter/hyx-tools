/*
 *  FILE %ds/hyxp/hyxp0010.c
 *
 *  Erzeugung von Text Elementen
 *
 *  written:       1991 03 12
 *                 1991 03 27
 *                 1995-03-30: moved to %ds/hyxp
 *  latest update: 1996-02-18 21:21:44
 *  $Id: hyxp0010.c,v 1.3 2004/05/08 15:40:21 gonter Exp $
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <gg/parse.h>

/* ------------------------------------------------------------------------ */
long _hyx_text_allocated= 0L;

/* ------------------------------------------------------------------------ */
struct TEXT_ELEMENT *hyx_mktx_elem (long lev, int typ)
{
  struct TEXT_ELEMENT *tx;

  if ((tx= (struct TEXT_ELEMENT *) calloc (sizeof (struct TEXT_ELEMENT), 1))
      != (struct TEXT_ELEMENT *) 0)
  {
    _hyx_text_allocated++;

    tx->sig= SIG_TEXT_ELEMENT;
    tx->TE_level= lev;
    tx->TE_link_count= 1;
    tx->TE_type= typ;
  }

  return tx;
}
