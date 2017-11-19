/*
 *  FILE ~/usr/ned/08/ned0834.c
 *
 *  Evaluierung eines Strings
 *
 *  written:       1991 05 23
 *  latest update: 1998-08-16 12:40:07
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include "ed.h"
#include "edhyx.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int ned_eval_string (char *str, int option)
{
  struct SGML_TAG_DESCRIPTOR *std;

ned_message_2 ("eval_string: ", str);
  /* Suchen der 'zustaendigen' Feature Type Definition */
  if ((std= find_sgml_tag_descriptor (str))
        == (struct SGML_TAG_DESCRIPTOR *) 0
      || std->STD_activated == (void *) 0) return 0;

  /* Aufruf der Handler Funktion */
  return (*std->STD_activated) (str, option);
}
