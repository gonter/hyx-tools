/*
 *  FILE %ds/entity/ent_0004.c
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

#include <gg/dpp.h>
#include <gg/entity.h>

/* ------------------------------------------------------------------------ */
struct ENTITY_DESCRIPTOR *entity_find_by_code (
struct ENTITY_CONTEXT *ctx,
long code)
{
  struct ENTITY_DESCRIPTOR *ed= (struct ENTITY_DESCRIPTOR *) 0;
  struct YTREE *yt;
  char code_str [10];

  if (ctx != (struct ENTITY_CONTEXT *) 0)
  {
    if (code >= 0L && code <= 0x00FFL)
    {
      ed= ctx->ec_tbl [(int) code];
    }
    else
    {
      long_to_hex (code, code_str);

      if ((yt= ytree_lookup_word (ctx->ec_codes, code_str))
               != (struct YTREE *) 0
          && (yt->YT_flags & YTflag_EOW)
         )
       ed= (struct ENTITY_DESCRIPTOR *) yt->YT_info;
    }
  }

  return ed;
}
