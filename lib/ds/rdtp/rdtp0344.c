/*
 *  $Id: rdtp0344.c,v 1.3 2000/06/05 17:05:13 gonter Exp $
 *  FILE %ds/rdtp/rdtp0344.c
 *
 *  restructured dynamic text parser
 *  destroy an attribute
 *
 *  T2D: new parametrs:
 *  1. flag: release list
 *  2. free attribute value function
 *
 *  written:       1997-06-16
 *  latest update: 2000-06-05 18:05:18
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/dyb.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_destroy_attribute (struct SGML_ATTRIBUTE_LIST *av)
{
  if (av == (struct SGML_ATTRIBUTE_LIST *) 0) return -1;

  if (av->flags & SAf_name_malloced)  free_or_what (av->attribute_name);
  if (av->flags & SAf_value_malloced) free_or_what (av->attribute_value);

#ifdef __T2D__ /* 1997-06-16 18:35:39 */
  if (av->flags & SAf_value_dyb) dyb_destroy_block (av->attribute_value);
#endif /* __T2D__ 1997-06-16 18:35:39 */

  free (av);

  return 0;
}
