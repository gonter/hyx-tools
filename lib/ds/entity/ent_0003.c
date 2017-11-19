/*
 *  FILE %ds/entity/ent_0003.c
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

#include <gg/entity.h>

/* ------------------------------------------------------------------------ */
struct ENTITY_DESCRIPTOR *entity_find_by_name (
struct ENTITY_CONTEXT *ctx,
char *name)
{
  struct ENTITY_DESCRIPTOR *ed= (struct ENTITY_DESCRIPTOR *) 0;
  struct YTREE *yt;

  if (ctx != (struct ENTITY_CONTEXT *) 0
      && (yt= ytree_lookup_word (ctx->ec_names, name)) != (struct YTREE *) 0
      && (yt->YT_flags & YTflag_EOW)
     )
    ed= (struct ENTITY_DESCRIPTOR *) yt->YT_info;

  return ed;
}
