/*
 *  FILE %ds/entity/ent_0002.c
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

#include <stdlib.h>
#include <gg/strings.h>
#include <gg/entity.h>

/* ------------------------------------------------------------------------ */
int entity_destroy_context (struct ENTITY_CONTEXT *ec)
{
  struct ENTITY_DESCRIPTOR_LIST *el, *el2;
  struct ENTITY_DESCRIPTOR *ed;

  if (ec == (struct ENTITY_CONTEXT *) 0) return -1;

  for (el= ec->edl; el != (struct ENTITY_DESCRIPTOR_LIST *) 0; el= el2)
  {
    el2= el->next;

    if ((ed= el->ed) != (struct ENTITY_DESCRIPTOR *) 0)
    {
      free_or_what (ed->name);
      free_or_what (ed->string);
      free (ed);
    }

    free (el);
  }

  ytree_free (ec->ec_names);
  ytree_free (ec->ec_codes);
  free_or_what (ec->ec_name);

  return 0;
}
