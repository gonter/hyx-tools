/*
 *  FILE %ned/11/ned1112v.c
 *
 *  search for a string in the current line
 *  called from vi_dkey ()
 *
 *  Text search and replace functions
 *  see: C API documentation
 *
 *  written:       1997-01-06
 *  latest update: 1997-01-15 13:24:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <gg/strings.h>
#include "ed.h"
#include "proto.h"
#include <gg/window.h>

extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
#define MAX_MSTR 10
static char mstr2 [MAX_MSTR];
static int option= 0x00;
static int skip= 0;

/* ------------------------------------------------------------------------ */
int ned_vi_wc_find_str (
struct WINDOWCTRL *wc,
char *mstr,
int cnt,
int mode)
{
  if (wc == (struct WINDOWCTRL *) 0) return -1;

#ifdef USE_TK
  tk_resetcup ();
#endif
  skip= 0;
  option= 0;

  switch (mode)
  {
    case 't':
      skip= -1;
      break;

    case 'T':
      skip= +1;
    case 'F':
      option |= OPT_backward;
      break;
  }

  strcpy_max (mstr2, mstr, MAX_MSTR);
  return ned_lp_find_str (wc, wc->WC_act, mstr, option, cnt, skip);
}

/* ------------------------------------------------------------------------ */
void ned_vi_find_next ()
{
#ifdef USE_TK
  tk_resetcup ();
#endif

  if (aw != (struct WINDOWCTRL *) 0
      && ned_lp_find_str (aw, aw->WC_act, mstr2, option, 1, skip) == -1
     )
    vi_bell ();
}

/* ------------------------------------------------------------------------ */
void ned_vi_find_next_rev ()
{
  option= (option & OPT_backward) ? 0 : OPT_backward;
  skip *= -1;

  ned_vi_find_next ();
}
