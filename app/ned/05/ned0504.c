/*
 *  FILE %ned/05/ned0504.c
 *
 *  get line pointer given the line number
 *
 *  written:       1987 04 08
 *  latest update: 2001-02-11 16:34:52
 *  $Id: ned0504.c,v 1.2 2001/02/12 00:03:30 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct LINE *ned_get_line_by_nr (
register struct LINE *lp,
int *lnr)                       /* target line: 1 .. first line in file     */
                                /* wenn das File kuerzer ist,               */
                                /* dann letzte Zeile im File !!!            */
/* RETURN: (struct LINE *) 0 -> Fehler; sonst -> OK                         */
{
  struct LINE *lp_next;
  int dlnr;
  int xlnr= 1;

  if (lp == (struct LINE *) 0
      || *lnr < 0
     )
  {
    *lnr= 0;
    return (struct LINE *) 0;
  }

  /* zurueckspulen */
  for (; lp->prev != (struct LINE *) 0; lp= lp->prev);

  for (dlnr= *lnr-1; dlnr > 0; dlnr--)
  {
    if ((lp_next= lp->next) == (struct LINE *) 0) break;
    lp= lp_next;
    xlnr++;
  }

  *lnr= xlnr;
  return lp;
}
