/*
 *  FILE %ds/rdtp/rdtp0311.c
 *
 *  restructured dynamic text parser
 *
 *  written:       1996-06-23
 *  latest update: 1996-09-14 22:31:26
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <stdlib.h>
#include <gg/rdtp.h>
#include <gg/rdtp03.h>

/* ------------------------------------------------------------------------ */
struct SGML_BUILDUP *sgml_initialize_buildup ()
{
  struct SGML_BUILDUP *sgml_build= (struct SGML_BUILDUP *) 0;

  if ((sgml_build= (struct SGML_BUILDUP *)
                   calloc (sizeof (struct SGML_BUILDUP), 1))
                   != (struct SGML_BUILDUP *) 0)
  {
    sgml_build->append= &sgml_build->document;
  }

  return sgml_build;
}
