/*
 *  FILE %ned/08/ned0843.c
 *
 *  Evaluieren einer Makro Definiton
 *
 *  written:       1991 05 24
 *  latest update: 1996-11-03 18:24:22
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <gg/dpp.h>
#include <gg/hyx.h>
#include "ed.h"
#include "proto.h"

/* ------------------------------------------------------------------------ */
int eval_ned_macro (char *s, int option)
{
#ifdef __SECURITY__PROBLEM__ /* 1996-11-03 18:23:38 */
  int mac_siz;
  int mac_num= 0;
  int evaluate_macro_immediately= 0;
  int macro_type= MPt_key_sequence;
  char *p;

  option= 0;

  if ((p= find_attr_name (s, "n")) != (char *) 0)
    mac_num= (int) get_parameter_value (p);
  mac_undef (mac_num);

  if ((p= find_attr_name (s, "ex")) != (char *) 0)
    evaluate_macro_immediately= (int) get_parameter_value (p);

  if ((p= find_attr_name (s, "ty")) != (char *) 0
     && (strncmp (p, "tcl", 3) == 0 || strncmp (p, "\"tcl\"", 5) == 0))
    macro_type= MPt_tcl;

  if ((p= find_attr_name (s, "s")) == (char *) 0) return -1;

  /******************** ###################
  if (*p == '\"') *p++;
  p [strlen (p)-1]= 0;
  ****************************************/

  mac_siz= trans_str (p, p, 9999);
  mac_define (mac_num, macro_type, p, mac_siz);
  if (evaluate_macro_immediately == 1) p_macro (mac_num);

#else
#ifdef MSDOS
  s; option;
#endif
#endif /* !__SECURITY__PROBLEM__ 1996-11-03 18:23:38 */

  return 0;
}
