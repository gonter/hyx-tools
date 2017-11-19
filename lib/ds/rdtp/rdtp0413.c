/*
 *  FILE %ds/rdtp/rdtp0413.c
 *
 *  restructured dynamic text parser
 *  process a declaration
 *
 *  written:       1996-09-15
 *  latest update: 1996-09-22 14:43:36
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gg/strings.h>
#include <gg/rdtp.h>
#include <gg/rdtp01.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
int sgml_print_element_declaration (
FILE *fo,
struct SGML_ELEMENT_DECLARATION *ed)
{
  fprintf (fo, "element: '%s'\n", ed->name);
  fprintf (fo, "  minimization: start=%c end=%c\n",
           (ed->minim_start) ? 'O' : '-',
           (ed->minim_end) ? 'O' : '-');

  sgml_print_attlist_declaration (fo, ed->attlist);
  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_print_attlist_declaration (
FILE *fo,
struct SGML_ATTLIST_DECL *attl)
{
  struct SGML_ATTRIBUTE_DECLARATION *attdecl;

  if (attl == (struct SGML_ATTLIST_DECL *) 0) return 0;

  fprintf (fo, "  attributes:\n");
  fprintf (fo, "    references: %d\n", attl->ref_count);

  for (attdecl= attl->attributes;
       attdecl != (struct SGML_ATTRIBUTE_DECLARATION *) 0;
       attdecl= attdecl->next)
    sgml_print_attribute_declaration (fo, attdecl);

  return 0;
}

/* ------------------------------------------------------------------------ */
int sgml_print_attribute_declaration (
FILE *fo,
struct SGML_ATTRIBUTE_DECLARATION *attdecl)
{
  fprintf (fo, "    attribute: name='%s' decval=%d defval=%d\n",
           attdecl->name, attdecl->declared_value, attdecl->default_value);

  return 0;
}
