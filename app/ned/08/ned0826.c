/*
 *  FILE %ned/08/ned0826.c
 *
 *  written:       1991 06 25: Revision
 *  latest update: 1996-07-26  3:15:10
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int find_feature (
struct LINE *lp,                /* line to start from                       */
int direction,                  /* Bit 0==0: up                             */
                                /*     0==1: down                           */
                                /*     1==0: Start @lp                      */
                                /*     1==1: Start @(top|bottom)            */
char *feature_name,             /* name of feature to search                */
struct LINE **found_line,       /* line of found feature                    */
int *nr_found_line,             /* number of found feature (preset!!!)      */
struct FEATURE **found_feature) /* feature to start from if available       */
/* Return: -1 ... error                                                     */
/*          0 ... feature not found                                         */
/*          1 ... feature found                                             */
{
  struct LINE *fl;
  struct FEATURE *ft;
  int lin_num;
  int fnl;
  char *tp;

  if (lp == (struct LINE *) 0) return -1;

  lin_num= *nr_found_line;
  fnl= strlen (feature_name);

  if (direction & 0x02)         /* lp an Anfang oder Ende stellen?          */
  {
    if (direction & 0x01)
    { /* lp an den Anfang des Files stellen */
      for (; lp->prev != (struct LINE *) 0; lp= lp->prev);
      lin_num= 1;
    }
    else
    { /* lp an das Ende des Files stellen */
      for (; lp->next != (struct LINE *) 0; lp= lp->next) lin_num++;
    }
  }

  /* find next feature in same line, if a valid feature is given */
  if (lp != (struct LINE *) 0 && *found_feature != (struct FEATURE *) 0)
    for (ft= lp->ftr; ft != (struct FEATURE *) 0; ft= ft->ftr_next)
      if (ft == *found_feature) goto NEXT_IN_LINE;

  while (lp != (struct LINE *) 0)
  {
    for (ft= lp->ftr; ft != (struct FEATURE *) 0; ft= ft->ftr_next)
    {
NEXT_IN_LINE:
      fl= (struct LINE *) ft->ftr_text_line;
      if (fl != (struct LINE *) 0
          && fl->txt != (struct TXT *) 0
          && (tp= fl->txt->t) != (char *) 0
          && strncmp (&tp[1], feature_name, fnl) == 0
          && (tp[fnl+1] == ' ' || tp[fnl+1] == '>'))
      {
        *found_line= lp;
        *nr_found_line= lin_num;
        *found_feature= ft;
        return 1;
      }
    }

    if (direction & 0x01)
    {
      lp = lp->next;
      lin_num++;
    }
    else
    {
      lp = lp->prev;
      lin_num--;
    }
  }

  return 0;
}
