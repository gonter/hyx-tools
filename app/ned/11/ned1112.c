/*
 *  FILE %ned/11/ned1112.c
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1997-01-06
 *  latest update: 1997-09-07 13:22:46
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#else
#include <gg/strings.h>
#endif

#include <string.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>

/* ------------------------------------------------------------------------ */
int ned_lp_find_str (
struct WINDOWCTRL *wc,
struct LINE *lp,
char *mstr,
int option,
int cnt,
int skip)
{
  int rc= 0;
  int msp, mln;
  struct LINE *mline;

  msp= get_coln (wc);
  if (option & OPT_backward) msp--; else msp++;
  msp -= skip;

  for (; cnt > 0; cnt--)
  {
    rc= ned_str_match (lp, msp, lp,
                       (unsigned char *) mstr,
                       (unsigned char *) 0,               
                       -1, &mline, &msp, &mln, option);
  }

  if (rc == 0)
  { /* string was found */

    wc->WC_act= mline;
    wc->cx= msp - wc->hv + wc->ax + skip;

    /*** if (option & OPT_backward) wc->cx -= mln-1; ***/
  }

  return rc;
}
