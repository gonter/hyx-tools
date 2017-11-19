/*
 *  FILE %ned/08/ned0841b.c
 *
 *  eval token in context as a :tag command
 *
 *  written:       1997-01-06
 *  latest update: 1997-06-28 22:49:06
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"

#define MAX_STR 128
extern struct WINDOWCTRL *aw;

/* ------------------------------------------------------------------------ */
int q_eval_tag ()
{
  char str [MAX_STR];

  ned_set_marker (aw, '1');
  return (q_isolate_word (str, MAX_STR, CHARSET_token, 1) > 0
            && /* ned_eval_lookup_feature (str, 0) == 0 */
               ex_tag_command (str) == 0
         ) ? 0 : -1;
}
