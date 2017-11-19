/*
 *  FILE %ds/entity/ent_0001.c
 *
 *  entity management
 *
 *  written:       1996-06-09
 *  latest update: 1996-06-09 11:22:01
 *
 */

#ifdef MSDOS
#pragma check_stack(off)
#endif

#include <string.h>
#include <stdlib.h>
#include <gg/entity.h>

/* ------------------------------------------------------------------------ */
struct ENTITY_CONTEXT *entity_create_context (char *name)
{
  struct ENTITY_CONTEXT *ec= (struct ENTITY_CONTEXT *) 0;

  if ((ec= calloc (sizeof (struct ENTITY_CONTEXT), 1))
      != (struct ENTITY_CONTEXT *) 0
     )
  {
    ec->edl_append= &ec->edl;
    if (name != (char *) 0) ec->ec_name= strdup (name);
  }

  return ec;
}
