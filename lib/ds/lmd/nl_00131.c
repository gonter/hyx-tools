/*
 *  FILE %ds/lmd/nl_00131.c
 *
 *  construct a TERM structure by evaluating two term structures
 *
 *  The first list is an accumulator, the second list is the
 *  added structure.  The elements of the second list have to
 *  be copied, if they are added to the accumulator.
 *
 *  Elements of the accumulator are dropped without freeing.  (T2D)
 *
 *  written:       1994-08-27
 *  latest update: 1995-07-31
 *  $Id: nl_00131.c,v 1.2 2001/08/03 15:51:42 gonter Exp $
 *
 */

#include <stdio.h>
#include <gg/lookup.h>

/* ------------------------------------------------------------------------ */
struct DOCUMENT_INFO_LIST *lmd_dil_operator (
struct DOCUMENT_INFO_LIST *dil_op1, 
struct DOCUMENT_INFO_LIST *dil_op2,
long operation)
{
  struct DOCUMENT_INFO_LIST *dil_res= (struct DOCUMENT_INFO_LIST *) 0;
  struct DOCUMENT_INFO_LIST **dp= &dil_res;
  struct DOCUMENT_INFO_LIST *dd;
  struct DOCUMENT_INFO *di1, *di2;
  long v1, v2;
  long diff;

  for (;;)
  {
    if (dil_op1 == (struct DOCUMENT_INFO_LIST *) 0
        && dil_op2 == (struct DOCUMENT_INFO_LIST *) 0)
      break;

    if (dil_op1 == (struct DOCUMENT_INFO_LIST *) 0)
    {
      if (operation == WRint_logic_or)
      {
        for (;
             dil_op2 != (struct DOCUMENT_INFO_LIST *) 0;
             dil_op2= dil_op2->DIL_next)
        {
          if ((dd= lmd_dil_dup (dil_op2)) == (struct DOCUMENT_INFO_LIST *) 0)
            break;
          *dp= dd;
          dp= &dd->DIL_next;
        }
      }
      break;
    }

    if (dil_op2 == (struct DOCUMENT_INFO_LIST *) 0)
    {
      *dp= (struct DOCUMENT_INFO_LIST *) 0;
      if (operation == WRint_logic_or) *dp= dil_op1;
      return dil_res;
    }

    if ((di1= dil_op1->DIL) == (struct DOCUMENT_INFO *) 0)
    {
      fprintf (stderr, "nl_00131(66): internal error, no DI!\n");
      dil_op1= dil_op1->DIL_next;
      continue;
    }

    if ((di2= dil_op2->DIL) == (struct DOCUMENT_INFO *) 0)
    {
      fprintf (stderr, "nl_00131(73): internal error, no DI!\n");
      dil_op1= dil_op2->DIL_next;
      continue;
    }

    v1= di1->DI_document_id;
    v2= di2->DI_document_id;
    diff= v1 - v2;

#ifdef DEBUG
    printf ("nl_00131: id1=%ld id2=%ld =: diff=%ld, op=0x%lX\n",
            v1, v2, diff, operation);
#endif /* DEBUG */

    if (diff == 0L && (operation == WRint_logic_and
                       || operation == WRint_logic_or)
                      )
    { /* the documents is in both lists */
#ifdef DEBUG
      printf ("nl_00131: take 1, adv 1, adv 2\n");
#endif /* DEBUG */

      /* add the dil-info from the first list to the result */
      *dp= dil_op1;
      dp= &dil_op1->DIL_next;

#ifdef LMD_EXTENDED_MODEL
      di1->DI_pos[0] |= di2->DI_pos[0];
      /* T2D: 2001-08-03 this is used in the freedb search engine!
       * There needs to be a more general apporach than this!
       */
#endif /* LMD_EXTENDED_MODEL */

      dil_op1= dil_op1->DIL_next;
      dil_op2= dil_op2->DIL_next;
      continue;
    }

    if (diff < 0L)
    {
      if (operation == WRint_logic_or)
      {
#ifdef DEBUG
      printf ("nl_00131: take 1\n");
#endif /* DEBUG */
        *dp= dil_op1;
        dp= &dil_op1->DIL_next;
      }
#ifdef DEBUG
      printf ("nl_00131: adv 1\n");
#endif /* DEBUG */
      dil_op1= dil_op1->DIL_next;
      continue;
    }

    if (diff > 0L)
    {
      if (operation == WRint_logic_or)
      {
#ifdef DEBUG
      printf ("nl_00131: dup 2\n");
#endif /* DEBUG */
        if ((dd= lmd_dil_dup (dil_op2)) == (struct DOCUMENT_INFO_LIST *) 0)
          break;

        *dp= dd;
        dp= &dd->DIL_next;
      }
#ifdef DEBUG
      printf ("nl_00131: adv 2\n");
#endif /* DEBUG */
      dil_op2= dil_op2->DIL_next;
      continue;
    }

    fprintf (stderr, "nl_00131: internal error!!!\n");
    break;
  }

  *dp= (struct DOCUMENT_INFO_LIST *) 0;

  return dil_res;
}
