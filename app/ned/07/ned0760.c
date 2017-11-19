/*
 *  FILE %ned/07/ned0760.c
 *
 *  copy block
 *
 *  written:       1996-03-06
 *  latest update: 1999-04-25 16:32:30
 *  $Id: ned0760.c,v 1.4 2005/09/04 20:17:27 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/hytxt.h>

#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_markup_block_2 (
struct WINDOWCTRL *w,
const char *start_tag)
{
  const char *start_tag_list [1];
  const char *stop_tag_list [1];
  char *cp;

  if ((cp= hyx_make_stop_tag (start_tag)) == (char *) 0) return -1;

  start_tag_list [0]= start_tag;
  stop_tag_list [0]= cp;

  ned_markup_block (w, 1, start_tag_list, 1, stop_tag_list);
  free (cp);

  return 0;
}
