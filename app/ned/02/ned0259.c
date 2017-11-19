/*
 *  FILE %ned/02/ned0259.c
 *
 *  vi emulation: find associated object for a given tag
 *
 *  written:       1996-05-23
 *  latest update: 1996-05-27 10:32:58
 *  $Id: ned0259.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#include "ed.h"
#include "proto.h"

#ifdef MSDOS
#pragma check_stack(off)
#endif

/* ------------------------------------------------------------------------ */
int ex_tag_command (const char *str)
{
  while (*str && *str == ' ') str++;
  if (*str == 0) return -1;

  if (ned_eval_lookup_feature (str, 0) == 0
      || ned_eval_tag_entry (str) == 0
     ) return 0;

  return -1;
}
