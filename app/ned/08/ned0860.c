/*
 *  FILE %ned/08/ned0860.c
 *
 *  written:       1991 07 04
 *  latest update: 1996-07-26  4:06:27
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

static char *dir [] = {   "next",  "prev",  "menu",  "up" };
static int flgs  [] = { LL_next, LL_prev, LL_menu, LL_up  };

/* ------------------------------------------------------------------------ */
int check_logic_links (struct WINDOWCTRL *w)
{
  struct LINE *lp;
  struct FEATURE *fp;
  int lin;
  int i;
  int rc= 0;

  for (i= 0;i<4;i++)
  {
    fp= (struct FEATURE *) 0;
    if (find_feature_with_attribute (w->WC_act, 0x0003,
          "HLINK", "dir", dir[i], &lp, &lin, &fp) == 1
      ||find_feature_with_attribute (w->WC_act, 0x0003,
          "hyx.l", "dir", dir[i], &lp, &lin, &fp) == 1)
      rc |= flgs[i];
  }
  return rc;
}
