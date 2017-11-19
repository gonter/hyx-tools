/*
 *  FILE %ds/vieos/vieos203.c
 *
 *  destroy a index object and all it's associated memory
 *
 *  written:       1995-12-14
 *  latest update: 1997-01-15 11:29:01
 *
 */

#include <stdlib.h>
#include <tcl.h>
#include <gg/strings.h>
#include <gg/vieos.h>

/* ------------------------------------------------------------------------ */
void vieos_destroy_index (ClientData clientData)
{
  struct VIEOS_INDEX *idx;

  if ((idx= (struct VIEOS_INDEX *) clientData) != (struct VIEOS_INDEX *) 0
      && idx->VIEI_signature == SIG_VIEOS_INDEX
     )
  {
    free_or_what (idx->VIEI_name);
    free (idx);
  }
}

