/*
 *  FILE %ned/08/ned0868.c
 *
 *  written:       1991 06 25
 *  latest update: 1996-07-27  9:48:14
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

static char *LL[]= { "hyx.l ", " dir=" } ;

/* ------------------------------------------------------------------------ */
void p_logic_link_more ()
{
  ned_setup_feature_window (1, 0, 2, LL);
}

/* ------------------------------------------------------------------------ */
void p_link_more ()
{
  ned_setup_feature_window (1, 0, 1, LL);
}
