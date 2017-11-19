/*
 *  FILE %ned/08/ned0869.c
 *
 *  activate a frame in a cluster but do not create it if it did
 *  not exist before.
 *  [Note: before 1998-07-19, the frame was created]
 *  T2D: frame creation should be possible upon request or by
 *       passing a flag as a parameter [1998-07-19]
 *
 *  written:       1991 09 25
 *  latest update: 1998-08-15 11:28:40
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

extern struct WINDOWCTRL *aw;
static int create_mode= 0x00;

/* ------------------------------------------------------------------------ */
int ned_set_create_special (int flg)
{
  create_mode= (flg) ? 0x02 : 0x00;
  return 0;
}

/* ------------------------------------------------------------------------ */
struct FRAMECTRL *ned_activate_special (
const char *cl_name,
const char *fr_name,
int cr_mode)            /* -1.. use default; 0 .. don't create; 1.. create */
{
  switch (cr_mode)
  {
    case -1: cr_mode= create_mode; break;
    case  0: cr_mode= 0x00; break;
    default: cr_mode= 0x02; break;
  }

  return ned_activate_cl_fr (cl_name, fr_name, cr_mode,
                             FMT_SGML, (char *) 0, (char *) 0);
}
