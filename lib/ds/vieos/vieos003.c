/*
 *  FILE %ds/vieos/vieos003.c
 *
 *  destroy a complete context and all it's associated memory
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:25:05
 *
 */

#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/parse.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_context (ClientData clientData)
{
  struct VIEOS_CONTEXT *vc;

  if ((vc= (struct VIEOS_CONTEXT *) clientData) != (struct VIEOS_CONTEXT *) 0
      && vc->VC_signature == (long) SIG_VIEOS_CONTEXT
     )
  {
    free_or_what (vc->VC_name);

    /* T2D: remove subordinate objects and everything ... */
    ytree_process (vc->VC_SUB_CONTEXT,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_context);

    ytree_process (vc->VC_INDEX,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_index);

    ytree_process (vc->VC_MARKUP,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_markup);

    ytree_process (vc->VC_BLOCK,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_block);

#ifdef __NOT_YET__ /* 1996-03-19 10:57:17 */
    ytree_process (vc->VC_CLUSTER,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_cluster);
#endif /* __NOT_YET__ 1996-03-19 10:57:17 */

    ytree_process (vc->VC_GENERIC,
                   vieos_destructor_generic,
                   (void *) vieos_destroy_generic);
    free (vc);
  }
}
