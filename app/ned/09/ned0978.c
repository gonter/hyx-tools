/*
 *  FILE %ned/09/ned0978.c
 *
 *  parse a macro definition string
 *
 *  written:       1994-08-14: extracted from %ned/08/ned0908.c
 *  latest update: 1999-04-25 16:36:14
 *  $Id: ned0978.c,v 1.4 2006/04/09 08:10:24 gonter Exp $
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <string.h>
#include <gg/strings.h>
#include <gg/dpp.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int mac_definition (char *tok_num, const char *tok_text, int mac_type)
{
  int mac_num;
  int mac_siz;
  char *tmp= (char *) 0;

  mac_num= (int) get_parameter_value (tok_num);
  if (mac_num < 0 || mac_num >= N_MACRO) return -1;

  if (mac_type == MPt_key_sequence)
  {
    tmp= malloc (strlen (tok_text));
    mac_siz= trans_str (tok_text, tmp, 9999);
    tok_text= tmp;
  }
  else mac_siz= 1; /* dummy number, not really used */

  mac_undef (mac_num);
  mac_define (mac_num, mac_type, tok_text, mac_siz);

  free_or_what (tmp);

  return 0;
}
