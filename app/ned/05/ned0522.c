/*
 *  FILE %ned/05/ned0522.c
 *
 *  window stack management
 *
 *  written:       1991 10 13
 *  latest update: 1999-05-02  4:50:54
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
struct PLIST *winstack= (struct PLIST *) 0;

/* ------------------------------------------------------------------------ */
int winstack_push (struct WINDOWCTRL *w)
{
  struct PLIST *pl;

  if (winstack != (struct PLIST *) 0
     && winstack->PL_val == w) return 0;  /* insert only once at top */

  winstack_delete (w);
  if ((pl= (struct PLIST *) calloc (sizeof (struct PLIST), 1)) ==
     (struct PLIST *) 0) return -1;

  pl->PL_val= w;
  pl->PL_lnk= winstack;
  winstack= pl;

  return 0;
}

/* ------------------------------------------------------------------------ */
#ifdef JUNK
struct WINDOWCTRL *winstack_pop ()
{
  struct PLIST *pl;
  struct WINDOWCTRL *wc;

  if ((pl= winstack) == (struct PLIST *) 0) return (struct WINDOWCTRL *) 0;

  wc= pl->PL_val;
  winstack= pl->PL_lnk;
  free (pl);

  return wc;
}
#endif

/* ------------------------------------------------------------------------ */
int winstack_delete (struct WINDOWCTRL *w)
{
  struct PLIST *pl, **ppl;

  for (ppl= &winstack; (pl= *ppl) != (struct PLIST *) 0;)
  {
    if (pl->PL_val == w)
    { /* delete this entry */
      *ppl= pl->PL_lnk;
      free (pl);
      return 0;
    }
    else ppl= &pl->PL_lnk;
  }

  return 0;
}

/* ------------------------------------------------------------------------ */
struct WINDOWCTRL *winstack_get (int num)
{
  struct PLIST *pl;

  for (pl= winstack; pl != (struct PLIST *) 0; pl= pl->PL_lnk)
  {
    if (num <= 0) return pl->PL_val;
    num--;
  }

  return (struct WINDOWCTRL *) 0;
}
