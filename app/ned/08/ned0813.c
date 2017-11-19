/*
 *  FILE %ned/08/ned0813.c
 *
 *  Bearbeitung des Feature Files und des Restart Files
 *
 *  written:       1991 09 11
 *  latest update: 1996-07-27  9:45:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
void p_link_feature ()
{
  ned_setup_feature_window (0, 0, 0, (char **) 0);
}
