/*
 *  FILE %ds/vieos/vieos303.c
 *
 *  destroy a block object and all it's associated memory
 *
 *  written:       1995-12-16
 *  latest update: 1997-01-15 11:29:26
 *
 */

#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_block (ClientData clientData)
{
  struct VIEOS_BLOCK *vb;

  if ((vb= (struct VIEOS_BLOCK *) clientData) != (struct VIEOS_BLOCK *) 0
      && vb->VIEB_signature == SIG_VIEOS_BLOCK
     )
  {
    vb->VIEB_signature= 0L;             /* create an invalid signature      */
                                        /* in case someone comes across     */
                                        /* a dangling pointer...            */
    free_or_what (vb->VIEB_name);
    free (vb);
  }
}
