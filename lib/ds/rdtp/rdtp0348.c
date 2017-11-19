/*
 *  FILE %ds/rdtp/rdtp0348.c
 *
 *  restructured dynamic text parser
 *  add a attribute name/long-value pair to a tag's structure
 *
 *  written:       1997-07-14
 *  latest update: 1997-07-27 10:42:30
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct SGML_ATTRIBUTE_LIST *sgml_add_long_attribute (
struct SGML_OPENING_TAG *ot,
char *name,
long value)
{
  char value_str [24];

  sprintf (value_str, "%ld", value);
  return sgml_add_attribute (ot, name, value_str);
}
