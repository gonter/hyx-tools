/*
 *  FILE %ned/08/ned0878.c
 *
 *  written:       1991 10 12
 *  latest update: 1995-11-28
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

#define STR_SIZE 256
static char str_cluster [STR_SIZE];
static char str_frame [STR_SIZE];
static int datinit= 0;

/* ------------------------------------------------------------------------ */
void ned_p_activate_cl_fr ()
{
  if (!datinit)
  {
    str_cluster [0]= 0;
    str_frame [0]= 0;
  }

  if (rd_str ("cluster: ", str_cluster, STR_SIZE) == -1
      || rd_str ("frame: ", str_frame, STR_SIZE) == -1
     ) return;

  ned_activate_special (str_cluster, str_frame, 1);
}
