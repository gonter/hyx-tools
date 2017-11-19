/*
 *  FILE %ds/rdtp/rdtp0422.c
 *
 *  restructured dynamic text parser
 *  process a declaration
 *
 *  written:       1996-09-15
 *  latest update: 1999-04-25 16:58:09
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
struct SGML_CONTENT_MODEL *sgml_get_content_model (
struct ARRAY_CONTROL *token_list)
{
  struct SGML_CONTENT_MODEL *cm;

  if ((cm= sgml_new_content_model ()) != (struct SGML_CONTENT_MODEL *) 0)
  {
    /* T2D: a lot is here to do !!! */
    cm->tmp= token_list;
  }

  return cm;
}
