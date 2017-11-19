/*
 *  FILE %ned/03/ned0334b.c
 *
 *  insert an entity string as a character
 *
 *  written:       1996-06-09
 *  latest update: 1998-08-16 12:26:47
 *  $Id: ned0334b.c,v 1.2 2005/09/04 18:36:07 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "proto.h"
#include <gg/convent.h>

/* ------------------------------------------------------------------------ */
int ned_enter_entity (const char *str)
{
  int ch;

  if ((ch= find_pc_sgml_entity (str)) == -1)
    ned_message_1 ("unknown entity");
  else q_insert (ch, 1);

  return ch;
}
