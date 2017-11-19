/*
 *  FILE %ned/05/ned0517.c
 *
 *  written:       1991 01 28: aus NED0726.C isoliert
 *                 1991 07 10: Revision
 *  latest update: 1999-04-25 16:31:47
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "ed.h"
#include "proto.h"
#include "message.h"

/* ------------------------------------------------------------------------ */
int ned_copy_line (
struct LINE **dl,               /* Destination Line                         */
struct LINE *sl)                /* Source Line                              */
/* RETURN: -1 ... error                                                     */
/*         0 ... ok                                                         */
{
  struct LINE *nl;              /* New Line */
  register struct TXT **tx1, *tx1b, *tx2;

  /* 1. copy line control data */
  if (sl == (struct LINE *) 0
      || (nl= alloc_line ()) == (struct LINE *) 0
     ) goto ERROR;

  nl->lng= sl->lng;
  nl->line_flg= sl->line_flg & LINE_BLOCK_CLR;         /* reset Block Flags */

  /* 2. copy all features */
  if (sl->ftr != (struct FEATURE *) 0
      && ned_copy_feature_list (&nl->ftr, sl->ftr) == -1
     ) goto ERROR;

  /* 3. copy text segments for the line */
  tx2= sl->txt;
  tx1= &nl->txt;
  while (tx2 != (struct TXT *) 0)
  {
    if ((*tx1= tx1b= txch_alloc (tx2->t_lng, 0x20)) == (struct TXT *) 0)
       goto ERROR;

    memcpy (tx1b->t, tx2->t, tx2->t_lng);
    tx1= &tx1b->next;
    tx2= tx2->next;
  }

  *dl= nl;
  return 0;

ERROR:
  ned_error_message (ERR_MEMORY);
  return -1;
}
